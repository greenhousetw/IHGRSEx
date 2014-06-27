#ifndef DEVICEPORTAL_H
#define DEVICEPORTAL_H

#include "deviceportal_global.h"
#include "../SensorBase/sensorbase.h"
#include "../DeviceBase/devicebase.h"
#include "../ControlHardwareManager/controlhardwaremanager.h"

class DEVICEPORTALSHARED_EXPORT DevicePortal : public QObject
{
    Q_OBJECT

public:
    DevicePortal();
    ~DevicePortal();

    bool Initialize();

private:
    QHash<QString, SensorBase*> sensorlist;
    ControlHardwareManager controlHWManager;
    bool InitializeSensors();
    bool MakeSensorControlHWManagerConnection();
    bool ClearSensorList();
};

#endif // DEVICEPORTAL_H
