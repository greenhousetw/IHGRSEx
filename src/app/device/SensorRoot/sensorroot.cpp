#include "sensorroot.h"


SensorRoot::SensorRoot()
{
    this->id="";
}

void SensorRoot::SetSensorInfo(QString id, CommonVariables::SensorType type)
{
    this->id=id;
    this->sensorType=type;
}

QString SensorRoot::GetSensorID()
{
    return this->id;
}

CommonVariables::SensorType SensorRoot::GetSensorType()
{
    return this->sensorType;
}

void SensorRoot::ReceieveData(DataPacket data)
{
}

