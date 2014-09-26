#ifndef TRANCEIVER_H
#define TRANCEIVER_H


#include <QVariant>
#include <QMap>
#include "../../device/Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class Tranceiver : public IHardware
{

public:

    Tranceiver();

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
    CommonVariables::TranceiverType trancieverType=CommonVariables::NotDefineDevice;
    double value=std::numeric_limits<double>::min();
};

#endif // TRANCEIVER_H
