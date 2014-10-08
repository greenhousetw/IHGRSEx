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
       bool isMe=false;

       foreach(QString key, package.notificationContent.keys())
       {
           CommonVariables::SensorType sensorKind=CommonVariables::GetSensorKindFromUnitIndex(key);

           if(this->sensorType == sensorKind)
           {
              isMe=true;
              this->value=package.notificationContent[key].toDouble();
              break;
           }
       }

       if(isMe)
       {
           qDebug()<<"value=" + QString::number(this->value);
           DataPacket dataPacket;
           //dataPacket.packetData.value="{\"controlboxid\" : \""+ this->controlBoxId + "\", \"id\" : \"" + this->id + "\", \"sensortype\" : \"" + this->GetDeviceType() + "\"}";
           dataPacket.packetData.value=this->controlBoxId + "," + this->id + "," + this->GetDeviceType() + "," + QString::number(this->value);
           dataPacket.packetData.payload=QVariant(CommonVariables::SensorUISettingString);
           emit this->SendData(dataPacket);
       }
    }
}

bool Sensor::SetHardware(QMap<QString, QVariant> config)
{
    bool result=false;

    this->id=config["id"].toString();
    this->controlBoxId=config["controlBoxid"].toString();

    QMetaObject metaObject = CommonVariables::staticMetaObject;
    QMetaEnum m=metaObject.enumerator(metaObject.indexOfEnumerator("SensorType"));

    QString type="type";

     for (int i=0; i < m.keyCount(); ++i)
     {
         if(config[type].toString() == QString(m.valueToKey(i)))
         {
            this->sensorType=(CommonVariables::SensorType) m.keyToValue(config[type].toString().toLocal8Bit().data());
            qDebug()<<"This device type=" + config[type].toString() + ", its index=" + QString::number(i);
            break;
         }
     }

     if(this->repository)
     {
         QMap<QString, QString> sqlCommand;
         sqlCommand.insert("SelectSelf", "Select * from SensorRecord where SensorRecord.SensorId='" + this->id + "'");

         if(this->repository->ExecuteSQLCommand(sqlCommand)[CommonVariables::SqlSelectSize].toInt()==0)
         {
            qDebug()<<"No this data";

            sqlCommand.clear();
            sqlCommand.insert("GetSensorId", "Select SensorType.ID from SensorType where SensorType.Name='" + this->GetDeviceType() + "'");
            this->repository->ExecuteSQLCommand(sqlCommand);
         }

         sqlCommand.clear();
     }

     result=true;

     return result;
}

bool Sensor::SetRepository(IRepository* repository)
{
    bool result=false;

    if(repository)
    {
        this->repository=repository;
        result=true;
    }

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

