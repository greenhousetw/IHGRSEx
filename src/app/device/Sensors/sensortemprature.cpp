#include "sensortemprature.h"


SensorTemprature::SensorTemprature()
{
}

SensorTemprature::SensorTemprature(QString id, SensorBase::SensorType sensorType)
    :SensorBase(id, sensorType)
{
}

void SensorTemprature::ControlHWMgrDataSlot(NotifyPackage package)
{
    if(package.target==this->id)
    {
        this->algorithm->ExecuteOperation(package.notificationContent[""]);
    }
}


