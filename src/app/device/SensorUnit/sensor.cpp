#include "sensor.h"


Sensor::Sensor()
{

}

bool Sensor::CoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    connect(core, SIGNAL(CoreSensorBus(NotifyPackage)), this, SLOT(ReceieveData(NotifyPackage)));
    connect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));

    result=true;

    return result;
}

bool Sensor::DiconnectCoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    disconnect(core, SIGNAL(CoreSensorBus(NotifyPackage)), this, SLOT(ReceieveData(NotifyPackage)));
    disconnect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));
    result=true;

    return result;
}

void Sensor::ReceieveData(DataPacket data)
{
    qDebug()<<"this method will not use";
}

void Sensor::ReceieveData(NotifyPackage package)
{
    if(package.target==this->controlBoxId)
    {
        qDebug() << "sensor id=" + this->id;
    }
}

bool Sensor::SetHardware(QMap<QString, QVariant> config)
{
    bool result=false;

    this->id=config["id"].toString();
    this->controlBoxId=config["controlBoxid"].toString();

    QMetaObject metaObject = CommonVariables::staticMetaObject;
    QMetaEnum m=metaObject.enumerator(metaObject.indexOfEnumerator("SensorType"));

     for (int i=0; i < m.keyCount(); ++i)
     {
         if(config["sensortype"].toString() == QString(m.valueToKey(i)))
         {
            this->sensorType=(CommonVariables::SensorType) m.keyToValue(config["sensortype"].toString().toLocal8Bit().data());
            qDebug()<<"This device type=" + config["sensortype"].toString() + ", its index=" + QString::number(i);
            break;
         }
     }

    result=true;

    return result;
}

QString Sensor::GetDeviceValue()
{
  return QString::number(this->value);
}

QString Sensor::GetDeviceID()
{
  return this->id;
}

QString Sensor::GetDeviceType()
{
  QString deviceType="";

  if(this->sensorType != CommonVariables::NotDefine)
  {
      QMetaObject metaObject = CommonVariables::staticMetaObject;
      QMetaEnum m=metaObject.enumerator(metaObject.indexOfEnumerator("SensorType"));
      deviceType=m.valueToKey(this->sensorType);
  }

  qDebug()<<"Sensor Type=" + deviceType;

  return deviceType;
}

