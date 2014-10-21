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
    QString algorithmString="algorithm";

     for (int i=0; i < m.keyCount(); ++i)
     {
         if(config[type].toString() == QString(m.valueToKey(i)))
        {
            this->sensorType=(CommonVariables::SensorType) m.keyToValue(config[type].toString().toLocal8Bit().data());
            qDebug()<<"This device type=" + config[type].toString() + ", its index=" + QString::number(i);
            break;
         }
     }

     // get algorithm loader
     if(config.contains(algorithmString))
     {
         QStringList algorithmList=config[algorithmString].toString().split(';');
         QString loaderName=algorithmList[0];
         QString algorithmName=algorithmList[1];

         if(loaderName.length() > 0 && loaderName!="None")
         {
             if(PluginHelper::GetPlugIn(this->algorithmLoader, loaderName))
             {
                 this->algorithmLoaderFactory= qobject_cast<IAlgorithmFactory *>(this->algorithmLoader.instance());
             }

             if(this->algorithmLoaderFactory!=NULL && !this->algorithmLoaderFactory->GetIAlgorithm(algorithmName, this->algorithm))
             {
                 qCritical()<<"algorithm load fail";
                 goto orz;
             }
         }

         this->algorithmLoader.unload();
     }

     if(this->repository)
     {
         QMap<QString, QString> sqlCommand;
         sqlCommand.insert("SelectSelf", "Select * from SensorRecord where SensorRecord.SensorId='" + this->id + "'");

         // If this sensor is not in the DB
         if(!this->repository->ExecuteSQLCommand(sqlCommand).next())
         {
              sqlCommand.clear();
              sqlCommand.insert("GetSensorType", "Select SensorType.ID from SensorType where SensorType.Name='" + config[type].toString() + "'");
              QSqlQuery query=this->repository->ExecuteSQLCommand(sqlCommand);

              // The given sensor type is valid
              while(query.next())
              {
                  sqlCommand.clear();
                  sqlCommand.insert("InserSensor","insert into SensorRecord (ControlBoxId, SensorTypeId, SensorId, UpdatedTime, Value, Deleted) values ('" +
                                    this->controlBoxId + "','" + query.value(0).toString() +"','" + this->id + "', '" + QDateTime::currentDateTime().toString("yyyy MM dd hh:mm:ss") + "', NULL ,0)");

                  // insert this sensor into DB
                  query=this->repository->ExecuteSQLCommand(sqlCommand);
              }
         }
         else
         {
             qDebug()<<"This sensor:" + this->id + " has been in the DB already";
         }
     }

     result=true;

     orz:
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
    // incoming target is matched to this sensor's controlBoxId
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

       // update fields: Value and UpdatedTime of table: SensorRecord
       if(isMe)
       {
           QMap<QString, QString> sqlCommand;
           sqlCommand.insert("UPDATERECORD", "update SensorRecord SET Value=" + QString::number(this->value) + ", UpdatedTime='" +
                             QDateTime::currentDateTime().toString("yyyy MM dd hh:mm:ss") +
                             "' where SensorId='" + this->id + "'");

           //update value
           this->repository->ExecuteSQLCommand(sqlCommand);

           // Prepare data for json transformation
           QMap<QString, QVariant> jsonData;
           jsonData.insert("controlBoxId", this->controlBoxId);
           jsonData.insert("id", this->id);
           jsonData.insert("sensorType", this->GetDeviceType());
           jsonData.insert("value", QString::number(this->value));

           // Send data back to UI layer
           DataPacket dataPacket;           
           dataPacket.packetData.value=QString(QJsonDocument::fromVariant(QVariant(jsonData)).toJson());
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
