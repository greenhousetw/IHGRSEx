#ifndef SENSORPLUGINLOADER_H
#define SENSORPLUGINLOADER_H

#include "../IDeviceFactory/idevicefactory.h"
#include "../SensorUnit/sensor.h"

class SensorPlugInLoader : public IDeviceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{fa0888e9-6421-469c-ad73-8089fb0f89e0}" FILE "info.json")
    Q_INTERFACES(IDeviceFactory)

public:
    SensorPlugInLoader();
    virtual IHardware* GetDevice(QMap<QString, QVariant>);
};

#endif // SENSORPLUGINLOADER_H
