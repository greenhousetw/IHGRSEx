#ifndef TRANCEIVER_H
#define TRANCEIVER_H


#include <QVariant>
#include <QMap>
#include "../../device/Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"
#include "../qextserialport/qextserialport.h"

class SerialPortMonitorThread;

class Tranceiver : public IHardware
{

public:

    Tranceiver();

public slots:

    virtual void ReceieveData(DataPacket data);
    virtual void ReceieveData(NotifyPackage data);

public:

    virtual bool SetHardware(QMap<QString, QVariant> config);
    virtual bool SetRepository(IRepository* repository);
    virtual QString GetDeviceValue();
    virtual QString GetDeviceID();
    virtual QString GetDeviceType();
    virtual bool CoreConnector(QObject&);
    virtual bool DiconnectCoreConnector(QObject&);
    bool ReceiveDataFromHardware();
    bool gterminate=false;

private:

    SerialPortMonitorThread* monitorThread;
    QextSerialPort *serialPort=NULL;
    QJsonObject jsonObject;
    QString id="";
    CommonVariables::TranceiverType trancieverType=CommonVariables::NotDefineDevice;
    double value=std::numeric_limits<double>::min();
    bool SendSerialDataToHardware(QString);   
    bool LoadConfig(QString);
};

/*!
 * This thread monitors communication events.
 */
class SerialPortMonitorThread: public QThread
{
    Tranceiver* tranciever;

    public:

        SerialPortMonitorThread(Tranceiver* tranciever);
        void stop();

    protected:
        //overriden
        virtual void run();
};

#endif // TRANCEIVER_H
