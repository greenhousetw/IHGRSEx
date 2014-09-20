#include "sensor.h"


Sensor::Sensor()
{

}

bool Sensor::CoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    connect(core, SIGNAL(CoreBus(DataPacket)), this, SLOT(ReceieveData(DataPacket)));
    connect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));

    result=true;

    return result;
}

bool Sensor::DiconnectCoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    disconnect(core, SIGNAL(CoreBus(DataPacket)), this, SLOT(ReceieveData(DataPacket)));
    disconnect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));
    result=true;

    return result;
}

void Sensor::ReceieveData(DataPacket data)
{
    if(data.packetData.payload.toString()=="Tranceiver")
    {
        //this->value=data.packetData.value.toDouble();

        qDebug()<<"sensor id gets the value:" + data.packetData.value;
    }
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

