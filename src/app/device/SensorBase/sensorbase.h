#ifndef SENSORBASE_H
#define SENSORBASE_H

#include "sensorbase_global.h"
#include "../DeviceBase/devicebase.h"
#include "../../sharelibs/NotifyPackage/notifypackage.h"
#include "../../algorithms/IAlgorithm/ialgorithm.h";
#include "../../sharelibs/CommonVariables/commonvariables.h"
#include <limits>

using namespace std;

class SENSORBASESHARED_EXPORT SensorBase : public DeviceBase
{
    Q_OBJECT

public:

    SensorBase();
    SensorBase(QString id);
    virtual bool SetAlgorithm(IAlgorithm* algorithm);

public slots:

virtual void ControlHWMgrDataSlot(NotifyPackage package);

protected:

    CommonVariables::SensorType sensorType=CommonVariables::NotDefine;
    IAlgorithm* algorithm;
    double value=std::numeric_limits<double>::min();    
};

#endif // SENSORBASE_H
