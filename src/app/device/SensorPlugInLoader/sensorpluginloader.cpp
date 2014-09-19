#include "sensorpluginloader.h"


SensorPlugInLoader::SensorPlugInLoader()
{
}

IHardware* SensorPlugInLoader::GetDevice(QMap<QString, QVariant> configs)
{
    IHardware *sensor=new Sensor;
    sensor->SetHardware(configs);
    return sensor;
}
