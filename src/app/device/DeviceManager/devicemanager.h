#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QList>
#include <QObject>
#include "../../core/Core/core.h"
#include "../../device/Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class IDeviceManager : public QObject
{

public:

    virtual bool SetCore()=0;
    virtual bool LoadSensors()=0;
    virtual bool LoadTranceievers()=0;
    virtual bool GetSensors()=0;
    virtual bool GetTranceievers()=0;
};

Q_DECLARE_INTERFACE(IDeviceManager, "{4a34bcdf-1458-4d7f-ba81-f2f0fa509ae9}")

#endif // DEVICEMANAGER_H