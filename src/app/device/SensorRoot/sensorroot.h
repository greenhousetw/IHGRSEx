#ifndef SENSORROOT_H
#define SENSORROOT_H

#include <QObject>
#include "../Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class SensorRoot : public IHardware
{   
    Q_OBJECT

public:

    SensorRoot();    

    void SetSensorInfo(QString id, CommonVariables::SensorType);
    QString GetSensorID();
    CommonVariables::SensorType GetSensorType();

public slots:

    virtual void ReceieveData(DataPacket data);

protected:

    QString id;
    double value=std::numeric_limits<double>::min();
    CommonVariables::SensorType sensorType=CommonVariables::NotDefine;
};
Q_DECLARE_INTERFACE(SensorRoot,"SensorRoot")
#endif // SENSORROOT_H
