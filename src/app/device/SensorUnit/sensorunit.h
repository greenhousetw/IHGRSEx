#ifndef SENSORUNIT_H
#define SENSORUNIT_H

#include "../SensorRoot/sensorroot.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class SensorUnit : public SensorRoot
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "SensorRoot" FILE "info.json")
    Q_INTERFACES(SensorRoot)

public:

    SensorUnit();

public slots:

    virtual void ReceieveData(DataPacket data);

};

#endif // SENSORUNIT_H
