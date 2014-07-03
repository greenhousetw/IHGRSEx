#include "sensor.h"


Sensor::Sensor()
{
}

Sensor::Sensor(QString id, CommonVariables::SensorType typeOfSensor)
    :SensorBase(id, typeOfSensor)
{
}

/**
 * @brief SensorController::ControlHWMgrDataSlot
 * package is from ControlHardwareManager, the package is from emit
 * @param package
 */
void Sensor::ControlHWMgrDataSlot(NotifyPackage package)
{
    if(package.target==this->id)
    {
        if(this->sensorType!=CommonVariables::NotDefine)
        {
           foreach(QString key, package.notificationContent.keys())
           {
              if(CommonVariables::GetSensorKindFromUnitIndex(key)==this->sensorType)
              {
                  QMetaObject metaObject = CommonVariables::staticMetaObject;
                  QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("SensorType"));
                  QString selectedSensorType(metaEnum.valueToKey(this->sensorType));
                  this->algorithm->dataStore.insert(selectedSensorType, package.notificationContent[key]);
                  qDebug()<<"sensor type=" + key + ", value="+package.notificationContent[key];
                  this->algorithm->ExecuteOperation();
              }
           }
        }
    }
}



