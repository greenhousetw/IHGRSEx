#include "tranceiver.h"


Tranceiver::Tranceiver()
{
}

bool Tranceiver::CoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    connect(core, SIGNAL(CoreBus(DataPacket)), this, SLOT(ReceieveData(DataPacket)));
    connect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));

    result=true;

    return result;
}

bool Tranceiver::DiconnectCoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    disconnect(core, SIGNAL(CoreBus(DataPacket)), this, SLOT(ReceieveData(DataPacket)));
    disconnect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));
    result=true;

    return result;
}

void Tranceiver::ReceieveData(DataPacket data)
{   
    if(data.packetData.payload.toString()=="Sensor")
    {
        this->value=data.packetData.value.toDouble();
        qDebug()<<"tranciever id gets the value:" + QString::number(this->value);
    }
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

    result=true;

    return result;
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
