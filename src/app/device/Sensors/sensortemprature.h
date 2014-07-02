#ifndef SENSORTEMPRATURE_H
#define SENSORTEMPRATURE_H

#include "sensors_global.h"
#include "../../algorithms/IAlgorithm/ialgorithm.h"
#include "../../algorithms/SimpleAlgorithm/simplealgorithm.h"
#include "../SensorBase/sensorbase.h"

class SENSORSSHARED_EXPORT SensorTemprature : public SensorBase
{
    Q_OBJECT

public:
    SensorTemprature();
    SensorTemprature(QString id);

public slots:

    virtual void ControlHWMgrDataSlot(NotifyPackage package);

private :

};

#endif // SENSORTEMPRATURE_H
