#ifndef SENSORBASE_H
#define SENSORBASE_H

#include "sensorbase_global.h"
#include "../DeviceBase/devicebase.h"
#include "../../sharelibs/NotifyPackage/notifypackage.h"
#include "../../algorithms/IAlgorithm/ialgorithm.h";
#include "../../sharelibs/CommonVariables/commonvariables.h"
#include "../../device/ControlHardwareManager/controlhardwaremanager.h"
#include <QObject>
#include <limits>
#include <QHash>
#include <QVariant>

using namespace std;

class SENSORBASESHARED_EXPORT SensorBase : public DeviceBase
{
    Q_OBJECT

public:

    SensorBase();
    SensorBase(QString id);
    SensorBase(QString id, CommonVariables::SensorType);
    virtual bool SetAlgorithm(IAlgorithm* algorithm);
    bool BuildHardwareInputConnection(ControlHardwareManager* controlHWMgr);

signals:

    void FreeSignal(QVariant package);

public slots:

virtual void ControlHWMgrDataSlot(NotifyPackage package);

protected:

    CommonVariables::SensorType sensorType=CommonVariables::NotDefine;
    IAlgorithm* algorithm;
    double value=std::numeric_limits<double>::min();    
};

#endif // SENSORBASE_H
