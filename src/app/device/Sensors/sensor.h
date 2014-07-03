#ifndef SENSORTEMPRATURE_H
#define SENSORTEMPRATURE_H

#include "sensors_global.h"
#include "../../algorithms/IAlgorithm/ialgorithm.h"
#include "../../algorithms/SimpleAlgorithm/simplealgorithm.h"
#include "../SensorBase/sensorbase.h"

class SENSORSSHARED_EXPORT Sensor : public SensorBase
{
    Q_OBJECT

public:
    Sensor();
    Sensor(QString id, CommonVariables::SensorType typeOfSensor);

public slots:

    virtual void ControlHWMgrDataSlot(NotifyPackage package);

private :

};

#endif // SENSORTEMPRATURE_H
