#include "sensorcontroller.h"


SensorController::SensorController()
{
}

SensorController::SensorController(QString id)
    :SensorBase(id)
{
}

/**
 * @brief SensorController::ControlHWMgrDataSlot
 * package is from ControlHardwareManager, the package is from emit
 * @param package
 */
void SensorController::ControlHWMgrDataSlot(NotifyPackage package)
{
    if(package.target==this->id)
    {
        foreach(QString key, package.notificationContent.keys())
        {
            CommonVariables::SensorType sensorkindString=CommonVariables::GetSensorKindFromUnitIndex(key);

            if(sensorkindString!=CommonVariables::NotDefine)
            {
                QMetaObject metaObject = CommonVariables::staticMetaObject;
                QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("SensorType"));
                QString selectedSensorType(metaEnum.valueToKey(sensorkindString));
                this->algorithm->dataStore.insert(selectedSensorType, package.notificationContent[key]);
                this->algorithm->ExecuteOperation();                               
                algorithm->dataStore.insert("Temprature", value);
                algorithm->dataStore.insert("id","1");
                qDebug("Hi");
            }
        }
    }
}
