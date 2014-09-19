#ifndef COREONE_H
#define COREONE_H

#include "./core.h"

class CoreOne : public ICore
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ICore" FILE "info.json")
    Q_INTERFACES(ICore)

public:

    QString GetCoreName();

    void CoreDataCollectBus(DataPacket data);

signals:

    virtual void CoreBus(DataPacket data);
};

#endif // COREONE_H
