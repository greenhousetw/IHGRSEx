#ifndef TRANCEIVER_H
#define TRANCEIVER_H


#include <QVariant>
#include <QMap>
#include "../../device/Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"
#include "../qextserialport/qextserialport.h"

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

    QextSerialPort *serialPort=NULL;
    QJsonObject jsonObject;
    QString id="";
    CommonVariables::TranceiverType trancieverType=CommonVariables::NotDefineDevice;
    double value=std::numeric_limits<double>::min();
    bool SendSerialDataToHardware(QString);
    bool ReceiveDataFromHardware();
    bool LoadConfig(QString);
};

#endif // TRANCEIVER_H
