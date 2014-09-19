#ifndef TRANCIEVERLOADER_H
#define TRANCIEVERLOADER_H

#include "../IDeviceFactory/idevicefactory.h"
#include "../Tranceiver/tranceiver.h"

class TrancieverLoader : public IDeviceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{664a1014-9bda-4793-a75a-7f32151edfe9}" FILE "info.json")
    Q_INTERFACES(IDeviceFactory)

public:
    TrancieverLoader();
    virtual IHardware* GetDevice(QMap<QString, QVariant>);
};

#endif // TRANCIEVERLOADER_H
