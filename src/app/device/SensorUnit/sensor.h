#ifndef SENSORUNIT_H
#define SENSORUNIT_H

#include <QVariant>
#include <QMap>
#include "../../device/Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class Sensor : public IHardware
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{a021a317-d070-4789-9935-89c2a8b4ddac}" FILE "info.json")
    Q_INTERFACES(IHardware)

public:

    Sensor();

public slots:

    virtual void ReceieveData(DataPacket data);

public:

    virtual bool SetHardware(QMap<QString, QVariant> config);
    virtual QString GetDeviceValue();
    virtual QString GetDeviceID();
    virtual QString GetDeviceType();

private:

    QString id="";
    CommonVariables::SensorType sensorType=CommonVariables::NotDefine;
    double value=std::numeric_limits<double>::min();
};

#endif // SENSORUNIT_H
