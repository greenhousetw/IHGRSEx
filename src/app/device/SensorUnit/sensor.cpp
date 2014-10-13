#include "sensor.h"

/*!
 * @brief  constructor of Sensor
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
Sensor::Sensor()
{

}

/*!
 * @brief  to initialize sensor internal data
 * @param  this collection stores values, which has id, controlBoxid
 * @return use boolean value to indicate initialization result
 * @retval true or false
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
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

         if(!this->repository->ExecuteSQLCommand(sqlCommand).next())
         {
              sqlCommand.clear();
              sqlCommand.insert("GetSensorType", "Select SensorType.ID from SensorType where SensorType.Name='" + config[type].toString() + "'");
              QSqlQuery query=this->repository->ExecuteSQLCommand(sqlCommand);

              while(query.next())
              {
                  sqlCommand.clear();
                  sqlCommand.insert("InserSensor","insert into SensorRecord (ControlBoxId, SensorTypeId, SensorId, UpdatedTime, Value, Deleted) values ('" +
                                    this->controlBoxId + "','" + query.value(0).toString() +"','" + this->id + "', '" + QDateTime::currentDateTime().toString("yyyy MM dd hh:mm:ss") + "', NULL ,0)");
                  query=this->repository->ExecuteSQLCommand(sqlCommand);

              }
         }
     }

     result=true;

     return result;
}

/*!
 * @brief  to set repository instance, which is from the file: repositoryconfig.json
 * @param  none NULL value of IRepository
 * @return use boolean value to indicate setting result
 * @retval true or false
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
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

/*!
 * @brief  purpose of this method is to establish connection between sensor and core
 * @param  none NULL ICore instance
 * @return use boolean value to indicate connection establishment is successful or not
 * @retval true or false
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
bool Sensor::CoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    connect(core, SIGNAL(CoreSensorBus(NotifyPackage)), this, SLOT(ReceieveData(NotifyPackage)));
    connect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));

    return result;
}

/*!
 * @brief  purpose of this method is to do disconnect between sensor and core
 * @param  none NULL ICore instance
 * @return use boolean value to indicate connection establishment is successful or not
 * @retval true or false
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
bool Sensor::DiconnectCoreConnector(QObject& coreIn)
{
    bool result=false;

    ICore* core= (ICore*) &coreIn;

    disconnect(core, SIGNAL(CoreSensorBus(NotifyPackage)), this, SLOT(ReceieveData(NotifyPackage)));
    disconnect(this, SIGNAL(SendData(DataPacket)), core, SLOT(CoreDataCollectBus(DataPacket)));
    result=true;

    return result;
}

/*!
 * @brief  this is a slot, which parses DataPacket incoming data to get right action
 * @param  none NULL NotifyPackage instance
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
void Sensor::ReceieveData(DataPacket data)
{
    qDebug()<<"this method will not use";
}

/*!
 * @brief  this is a slot, which parses NotifyPackage incoming data to get right action
 * @param  none NULL NotifyPackage instance
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
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

/*!
 * @brief  to get current sensed value
 * @return return value
 * @retval QString type
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
QString Sensor::GetDeviceValue()
{
  return QString::number(this->value);
}

/*!
 * @brief  to get id of this sensor
 * @return return id of this sensor
 * @retval QString type
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
QString Sensor::GetDeviceID()
{
  return this->id;
}

/*!
 * @brief  to get sensor type of this sensor
 * @return return sensor type
 * @retval QString type
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
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
