#include "coreone.h"
#include <QtPlugin>
#include <QDebug>


QString CoreOne::GetCoreName()
{
    return QString("Core One");
}

void CoreOne::CoreSensorCollectBus(DataPacket data)
{      
}

void CoreOne::CoreDataCollectBus(DataPacket data)
{
    qDebug()<<"CoreOne gets " + data.packetData.payload.toString() + ", CoreDataCollectBus";
    emit this->CoreDeviceManagerSignal(data);
}

void CoreOne::CoreDeviceManagerCollectionBus(DataPacket data)
{
    qDebug()<<"CoreOne gets data from DeviceManager";

    QVariantMap map=CommonLib::ParseJSon(data.packetData.value);

    foreach(QString key, map.keys())
    {
      if(key=="FakeCommand" && map[key].toString()==CommonVariables::FakeSensorRequest)
      {
          this->EmitPackageToSensor(map["value"].toString());
      }
      else if(map[key].toString()==CommonVariables::HWRequest)
      {
          data.packetData.payload=CommonVariables::TRANCIEVERHARDWARESENDMESSAGE;
          data.packetData.value=map["value"].toString();
          emit this->CoreTrancieverBus(data);
      }
    }
}

void CoreOne::CoreTrancieverCollectBus(DataPacket data)
{
     qDebug()<< "Tranciever sends data to CoreOne, the value:" + data.packetData.value;

     QString parsedData="";
     NotifyPackage package;

     if(this->ParseDataStream(data.packetData.value, &parsedData))
     {
         if(this->GetNotifyPackage(parsedData, &package))
         {
             emit this->CoreSensorBus(package);
         }
     }
}

void CoreOne::EmitPackageToSensor(QString inputStream)
{
    QString realData="";
    QStringList inputStreamList=inputStream.split('*');

    foreach(QString input, inputStreamList)
    {
        realData="";

        if(this->ParseDataStream(input, &realData))
        {
          NotifyPackage notifyPacket;
          this->GetNotifyPackage(realData, &notifyPacket);
          emit this->CoreSensorBus(notifyPacket);
        }
    }
}

bool CoreOne::ParseDataStream(QString dataStream, QString* realData)
{
    bool result=false;

    try{
          QString endingChar="*";
          qDebug()<<"CoreOne starts to parse incoming string=" + dataStream;
          QStringList dataList=dataStream.split(endingChar);
          QRegExp regExpression;

          if(dataStream.length() != 0)
          {
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

                  *realData=dataList[i].split(parityString)[0].remove(regExpression);
              }

              result=true;
          }
      }
      catch(std::exception& err)
      {
          qCritical()<<err.what();
      }

    orz:
    return result;
}

bool CoreOne::GetNotifyPackage(QString data, NotifyPackage* package)
{
    bool result=false;

    try{
        qDebug()<<"Start to encapsulate data:" + data;

        QMetaObject metaObject = CommonVariables::staticMetaObject;
        QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("CommandType"));
        package->commandType = (CommonVariables::CommandType) metaEnum.keyToValue(QString(data.at(0)).toLocal8Bit().data());

        QRegExp regularExpression;
        QString patternGetID="^[Q|C|R|S|D]\\d+";
        regularExpression.setPattern(patternGetID);

        if(data.indexOf(regularExpression)<0)
        {
            qCritical()<<"node id missing";
            goto orz;
        }

        QString nodeID=regularExpression.cap(0).remove(0,1);
        package->target=nodeID;
        regularExpression.setPattern("[^A-Za-z]+\\d+");
        QStringList keyList=data.split(regularExpression);
        keyList.removeLast();
        regularExpression.setPattern("[A-Za-z]+");
        QStringList valueList=data.split(regularExpression);
        valueList.removeFirst();

        for(int i=0;i<keyList.count();i++)
        {
            package->notificationContent.insert(keyList[i],valueList[i]);
        }

        result=true;
    }
    catch(std::exception& err)
    {
        qCritical()<<err.what();
    }

    orz:
    return result;
}

