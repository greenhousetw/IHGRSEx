#ifndef COREONE_H
#define COREONE_H

#include "./core.h"
#include "../../sharelibs/CommonLib/commonlib.h"

class CoreOne : public ICore
{
    Q_PLUGIN_METADATA(IID "{84fe3d35-1aad-4ed9-bdc0-de6bca42a0b7}" FILE "info.json")
    Q_INTERFACES(ICore)

public:

    virtual QString GetCoreName();

public slots:

    virtual void CoreDataCollectBus(DataPacket data);
    virtual void CoreTrancieverCollectBus(DataPacket data);
    virtual void CoreSensorCollectBus(DataPacket data);
    virtual void CoreDeviceManagerCollectionBus(DataPacket data);

private:

    IRepository* repository=NULL;

    void EmitPackageToSensor(QString);
    bool ParseDataStream(QString, QString* realData);
    bool GetNotifyPackage(QString, NotifyPackage*);
};

#endif // COREONE_H
