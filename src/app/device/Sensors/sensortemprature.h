#ifndef SENSORTEMPRATURE_H
#define SENSORTEMPRATURE_H

#include "sensors_global.h"
#include "../SensorBase/sensorbase.h"

class SENSORSSHARED_EXPORT SensorTemprature : public SensorBase
{
    Q_OBJECT

public:
    SensorTemprature();
    SensorTemprature(QString id, SensorBase::SensorType sensorType);

public slots:

    virtual void ControlHWMgrDataSlot(NotifyPackage package);
};

#endif // SENSORTEMPRATURE_H
