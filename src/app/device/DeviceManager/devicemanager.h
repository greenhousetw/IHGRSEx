#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include "../../core/Core/core.h";

class IDeviceManager : public QObject
{

private:

    ICore *core=NULL;

public:

    virtual bool SetCore()=0;
    virtual bool ScanSensors()=0;
    virtual bool ScanTranceievers()=0;
    virtual bool DetectSensor()=0;
};

Q_DECLARE_INTERFACE(IDeviceManager, "{4a34bcdf-1458-4d7f-ba81-f2f0fa509ae9}")

#endif // DEVICEMANAGER_H
