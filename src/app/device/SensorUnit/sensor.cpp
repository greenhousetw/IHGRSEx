#include "sensor.h"


Sensor::Sensor()
{

}

void Sensor::ReceieveData(DataPacket data)
{
}


bool Sensor::SetHardware(QMap<QString, QVariant> config)
{
    bool result=false;

    this->id=config["id"].toString();

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

