#ifndef SENSORTEMPRATURE_H
#define SENSORTEMPRATURE_H

#include "sensors_global.h"
#include "../SensorBase/sensorbase.h"

class SENSORSSHARED_EXPORT SensorController : public SensorBase
{
    Q_OBJECT

public:
    SensorController();
    SensorController(QString id);

public slots:

    virtual void ControlHWMgrDataSlot(NotifyPackage package);

};

#endif // SENSORTEMPRATURE_H
