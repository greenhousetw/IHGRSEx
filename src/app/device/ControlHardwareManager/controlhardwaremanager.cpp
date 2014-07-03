#include "controlhardwaremanager.h"


ControlHardwareManager::ControlHardwareManager()
{    
    QString fileName=QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QDir::separator() + "HardwareControlTable.js");
    QFile scriptFile(fileName);

    if (!scriptFile.open(QIODevice::ReadOnly))
    {
        qCritical()<<"failed to open file=" + fileName;
        throw QString("failed to open file=" + fileName);
    }
    else
    {
        QTextStream stream(&scriptFile);
        this->strScript = stream.readAll();
        scriptFile.close();
        this->jsEngine.evaluate(this->strScript);
        qDebug()<<":) file:" + fileName + " has been loaded";
    }
}

/**
 * @brief ControlHardwareManager::HardwareReceieverSlot
 * slot for receieving data which is from serial device (COM port or USB)
 * @param bundlData
 * this parameter will be sent by serial device
 */
void ControlHardwareManager::HardwareReceieverSlot(QString bundlData)
{
    this->ParseHardwareInputDataStream(bundlData);
}

/**
 * @brief ControlHardwareManager::ParseHardwareInputDataStream
 * based on the rule to parse data
 * @param dataStream, which is from method: HardwareReceieverSlot
 * @return true for successful and false for fail
 */
bool ControlHardwareManager::ParseHardwareInputDataStream(QString dataStream)
{
    bool result=false;

    try{
          QString endingChar="*";
          qDebug()<<"incoming string=" + dataStream;
          QStringList dataList=dataStream.split(endingChar);
          QRegExp regExpression;

          for (int i = 0; i < dataList.size(); ++i)
          {
              if(dataList[i].length()==0)
              {
                  continue;
              }

              dataList[i]=dataList[i]+endingChar;
              qDebug()<<"will process the string=" + dataList[i];

              QString paritySize="2";
              QString patternForSearchEnd="[A-Za-z|0-9]{" + paritySize + "}\\*";
              regExpression.setPattern(patternForSearchEnd);
              int pos=dataList[i].indexOf(regExpression);

              if(pos<0)
              {
                  continue;
              }

              // Get parity string
              QString parityString="";

              for(int index=0;index<regExpression.matchedLength()-1;index++)
              {
                  parityString=parityString+regExpression.cap(index);
              }

              parityString=parityString.left(parityString.length()-1);

              qDebug()<<"parity string=" + parityString;

              if(dataList[i].split(parityString).count()!=2)
              {
                  qDebug()<<dataList[i] + " is not a legal string";
                  continue;
              }

              QString realData=dataList[i].split(parityString)[0].remove(regExpression);
              qDebug()<<"Start to encapsulate data:" + realData;
              this->EncapsulatePackage(realData);
          }

          result=true;
      }
      catch(std::exception& err)
      {
          qCritical()<<err.what();
      }

      return result;
}
/**
 * @brief ControlHardwareManager::EncapsulatePackage
 * To encapsulate parsed data into NotifyPackage, then send to PushSerialSlotDataOut
 * @param data
 * @return true for successful and false for fail
 */
bool ControlHardwareManager::EncapsulatePackage(QString data)
{
    bool result=false;

    try{
        qDebug()<<"Data ready to encapsulate=" + data;

        NotifyPackage package;
        QMetaObject metaObject = CommonVariables::staticMetaObject;
        QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("CommandType"));
        package.commandType = (CommonVariables::CommandType) metaEnum.keyToValue(QString(data.at(0)).toLocal8Bit().data());

        QRegExp regularExpression;
        QString patternGetID="^[Q|C|R|S|D]\\d+";
        regularExpression.setPattern(patternGetID);

        if(data.indexOf(regularExpression)<0)
        {
            qCritical()<<"node id missing";
            goto orz;
        }

        QString nodeID=regularExpression.cap(0).remove(0,1);
        package.target=nodeID;
        regularExpression.setPattern("[^A-Za-z]+\\d+");
        QStringList keyList=data.split(regularExpression);
        keyList.removeLast();
        regularExpression.setPattern("[A-Za-z]+");
        QStringList valueList=data.split(regularExpression);
        valueList.removeFirst();

        for(int i=0;i<keyList.count();i++)
        {
            package.notificationContent.insert(keyList[i],valueList[i]);
        }

        emit this->SignalInternalSubscribers(package);
        result=true;
    }
    catch(std::exception& err)
    {
        qCritical()<<err.what();
    }

    orz:
    return result;
}
/**
 * @brief ControlHardwareManager::ChangeHardwareStatus
 * This method is a slot method, which only disposes "C" command only
 * The method will call "HardwareControlTable.js" and use "gethardwareCtype"
 * as argument to get the full device control code.
 * for example:
 * machineStatusList contains record: "coolingfan.on", then you will get
 * control code:C03301, which will be passed to SendDataBySerial
 * @param machineStatusList
 * machine status list, which contains: coolingfan.on or etc.
 */
void ControlHardwareManager::CommandSlotC(QList<QString> machineStatusList)
{
    if(machineStatusList.count()>0)
    {
        QString commandMethod="gethardwareCtype";
        QScriptValue function=jsEngine.globalObject().property(commandMethod);
        QScriptValueList args;

        foreach (QString data, machineStatusList) {
            args << QScriptValue(data);
            QString result=function.call(QScriptValue(), args).toString();
            qDebug()<<"Script returns value=" + result;
            this->PassDataToHardwareDevice(result);
            args.clear();
        }
    }
    else
    {
        qDebug()<<"There is no any machine status should be changed~";
    }
}
/**
 * @brief ControlHardwareManager::ExcuteRSQCommand
 * This method is a slot method, which disposes "R", "S" or "Q" command
 * This method will call "HardwareControlTable.js" and based on command type
 * , which defined in the num:SupportCommandType with reflection tech. to
 * call the right function, then you can get the full device control code.
 * for example:
 * machineStatusList contains record: "room.humid", then you will get
 * control code:Q002, which will be passed to SendDataBySerial
 * @param nodeHash
 * machine status list, which contains: room.humid or etc.
 */
void ControlHardwareManager::CommandSlotRSQ(QHash<QString, QString> nodeHash)
{
    if(nodeHash.count()>0)
    {
        QMetaObject metaObject = ControlHardwareManager::staticMetaObject;
        QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("SupportCommandType"));
        QString selectedCommand(metaEnum.valueToKey(this->commandType));
        qDebug()<<"Enum command name=" + selectedCommand;
        QScriptValue function=jsEngine.globalObject().property(selectedCommand);
        QScriptValueList args;

        foreach (QString key, nodeHash.keys()) {
            args << nodeHash[key] << key;
            QString result=function.call(QScriptValue(), args).toString();
            qDebug()<<"Script returns value=" + result;
            this->PassDataToHardwareDevice(result);
            args.clear();
        }
    }
    else
    {
        qDebug()<<"There is no any machine status should be changed~";
    }
}
/**
 * @brief ControlHardwareManager::PassDataToHardwareDevice
 * pass data to USB or any hardware device sender
 * @param data
 */
void ControlHardwareManager::PassDataToHardwareDevice(QString data)
{
    data=data+this->GetParityString();
    // code for sending data through real hardware device   
    qDebug()<<"The data:" + data + " will be sent";
}

/**
 * @brief ControlHardwareManager::GetParityString
 * @return
 */
QString ControlHardwareManager::GetParityString()
{
    return "AA*";
}
