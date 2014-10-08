#include "tranceiver.h"


Tranceiver::Tranceiver()
{   
}

bool Tranceiver::CoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    connect(core, SIGNAL(CoreTrancieverBus(DataPacket)), this, SLOT(ReceieveData(DataPacket)));
    connect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreTrancieverCollectBus(DataPacket)));

    result=true;

    return result;
}

bool Tranceiver::DiconnectCoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    disconnect(core, SIGNAL(CoreTrancieverBus(DataPacket)), this, SLOT(ReceieveData(DataPacket)));
    disconnect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));
    result=true;

    return result;
}

void Tranceiver::ReceieveData(DataPacket data)
{        
    if(data.packetData.payload.toString()==CommonVariables::IHGRSSTOPWORKING)
    {
        if(this->serialPort)
        {
            this->serialPort->close();
            qDebug()<<"Serial port has been closed, port number=" + this->jsonObject["Port"].toString();
        }
    }
    else if(data.packetData.payload.toString()==CommonVariables::TRANCIEVERHARDWARESENDMESSAGE)
    {
        //this->SendSerialDataToHardware(data.packetData.value);
        this->ReceiveDataFromHardware();
    }
    else if(data.packetData.payload.toString()==CommonVariables::TRANCIEVERHARDWARERECEIEVEMESSAGE)
    {
        this->SendSerialDataToHardware(data.packetData.value);
    }
}

void Tranceiver::ReceieveData(NotifyPackage data)
{
    qDebug()<<"will not use this method";
}

bool Tranceiver::SetHardware(QMap<QString, QVariant> config)
{
    bool result=false;

    this->id=config["id"].toString();

    QMetaObject metaObject = CommonVariables::staticMetaObject;
    QMetaEnum m=metaObject.enumerator(metaObject.indexOfEnumerator("TranceiverType"));

     for (int i=0; i < m.keyCount(); ++i)
     {
         if(config["TranceiverType"].toString() == QString(m.valueToKey(i)))
         {
            this->trancieverType=(CommonVariables::TranceiverType) m.keyToValue(config["TranceiverType"].toString().toLocal8Bit().data());
            qDebug()<<"This device type=" + config["TranceiverType"].toString() + ", its index=" + QString::number(i);
            break;
         }
     }

    if(!this->LoadConfig("ihgrs.qserialport.json"))
    {
        qCritical()<<"cannot find configruation file: ihgrs.qserialport.json";
        goto orz;
    }

    if(this->serialPort == NULL)
    {
        this->serialPort=new QextSerialPort(this->jsonObject["Port"].toString());
        this->serialPort->setQueryMode(QextSerialPort::EventDriven);
        this->serialPort->setBaudRate(BAUD9600);
        this->serialPort->setFlowControl(FLOW_OFF);
        this->serialPort->setParity(PAR_NONE);
        this->serialPort->setDataBits(DATA_8);
        this->serialPort->setStopBits(STOP_1);

        int portopeningSuccessful=1;

        if(this->serialPort->open(QIODevice::ReadWrite|QIODevice::Unbuffered) == portopeningSuccessful)
        {
            qDebug()<<"Open com port=" + this->jsonObject["Port"].toString() + " is successful";
            //this->monitorThread=new SerialPortMonitorThread(this);
            //this->monitorThread->start();
        }
        else
        {
            qDebug()<<"Open com port=" + this->jsonObject["Port"].toString() + " is fail";
        }
    }

    result=true;

    orz:
    return result;
}

bool Tranceiver::SetRepository(IRepository* repository)
{
   return true;
}

QString Tranceiver::GetDeviceValue()
{
  return QString::number(this->value);
}

QString Tranceiver::GetDeviceID()
{
  return this->id;
}

QString Tranceiver::GetDeviceType()
{
  QString deviceType="";

  if(this->trancieverType != CommonVariables::NotDefineDevice)
  {
      QMetaObject metaObject = CommonVariables::staticMetaObject;
      QMetaEnum m=metaObject.enumerator(metaObject.indexOfEnumerator("TranceiverType"));
      deviceType=m.valueToKey(this->trancieverType);
  }

  qDebug()<<"Tranciever Type=" + deviceType;

  return deviceType;
}

bool Tranceiver::LoadConfig(QString fileName)
{
    bool result=false;

    QDir dir(QCoreApplication::applicationDirPath());

    QFile loadFile(dir.absoluteFilePath(fileName));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file:" + fileName;
        goto bye;
    }

    this->jsonObject=QJsonDocument::fromJson(loadFile.readAll()).object();

    result=true;

    loadFile.close();

    bye:
    return result;
}

bool Tranceiver::SendSerialDataToHardware(QString data)
{
    bool result=false;

    int returnLength = -1;

    int realReturnLength=this->serialPort->write(data.toLatin1(),data.toLatin1().length());

    if(realReturnLength==returnLength)
    {
        qWarning()<<"QSerialPort Error number=" + QString::number(this->serialPort->lastError());
        goto orz;
    }

    qDebug()<< "Data:" + data +" has been sent";

    result=true;

    orz:
    return result;
}

bool Tranceiver::ReceiveDataFromHardware()
{
    bool result=false;

    const int charSize=1024;

    const int checkReadLenght=-1;

    char buff[charSize];

    /*
    DataPacket packet;
    packet.packetData.value="Q01CP28H77A2990BB*";

    emit SendData(packet);
    */

    int numBytes = this->serialPort->bytesAvailable();

    if(numBytes > 0)
    {       
        if(numBytes > charSize)
        {
          numBytes = charSize;
        }

        qDebug()<<"IHGRS has read data length=" + QString::number(numBytes);

        int index = this->serialPort->read(buff, numBytes);

        if (index != checkReadLenght)
        {
           buff[index] = '\0';
        }
        else
        {
          buff[0] = '\0';
        }

        QString messageBox = QString::fromLatin1(buff);
        QByteArray qbyteArray=messageBox.toLatin1();

        DataPacket packet;
        packet.packetData.value=QString(qbyteArray);

        emit this->SendData(packet);

        messageBox.clear();
        qbyteArray.clear();
    }


    result=true;

    return result;
}

SerialPortMonitorThread::SerialPortMonitorThread(Tranceiver * tranciever):
    QThread()
{
    this->tranciever=tranciever;
    this->tranciever->gterminate = false;
}
void SerialPortMonitorThread::stop()
{
    this->tranciever->gterminate = true;
}
void SerialPortMonitorThread::run()
{
    this->tranciever->gterminate = false;

    int seconds=1000;

    while(!this->tranciever->gterminate)
    {
       QThread::msleep(seconds);
       this->tranciever->ReceiveDataFromHardware();
    }
}
