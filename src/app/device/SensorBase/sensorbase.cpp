#include "sensorbase.h"


SensorBase::SensorBase()
{
}

SensorBase::SensorBase(QString id, CommonVariables::SensorType sensorType)
{
    this->id=id;
    this->sensorType=sensorType;
}

bool SensorBase::SetAlgorithm(IAlgorithm *algorithm)
{
    if(algorithm!=NULL)
    {
        this->algorithm=algorithm;
    }
    else
    {
        qCritical()<<"algorithm is NULL, we can set algorithm for the sensor";
    }
}

void SensorBase::ControlHWMgrDataSlot(NotifyPackage package)
{

}
