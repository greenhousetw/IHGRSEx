#ifndef SENSORUNIT_H
#define SENSORUNIT_H

#include <QVariant>
#include <QMap>
#include "../../device/Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class Sensor : public IHardware
{

public:

    Sensor();

public slots:

    virtual void ReceieveData(DataPacket data);
    virtual void ReceieveData(NotifyPackage data);

public:

    virtual bool SetHardware(QMap<QString, QVariant> config);
    virtual QString GetDeviceValue();
    virtual QString GetDeviceID();
    virtual QString GetDeviceType();
    virtual bool CoreConnector(QObject&);
    virtual bool DiconnectCoreConnector(QObject&);

private:

    QString id="";
    QString controlBoxId="";
    CommonVariables::SensorType sensorType=CommonVariables::NotDefine;
    double value=std::numeric_limits<double>::min();      
};

#endif // SENSORUNIT_H
