#ifndef SENSORUNIT_H
#define SENSORUNIT_H

#include <QVariant>
#include <QMap>
#include "../../device/Hardware/hardware.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"
#include "../../algorithms/IAlgorithm/ialgorithm.h"
#include "../../algorithms/IAlgorithmFactory/ialgorithmfactory.h"
#include "../../algorithms/AlgorithmLoader/algorithmloader.h"
#include <QDateTime>

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
    virtual bool SetRepository(IRepository* repository);

private:

    QPluginLoader algorithmLoader;
    IAlgorithmFactory* algorithmLoaderFactory=NULL;
    IAlgorithm* algorithm=NULL;
    IRepository* repository=NULL;
    QString id="";
    QString controlBoxId="";
    CommonVariables::SensorType sensorType=CommonVariables::NotDefine;
    double value=std::numeric_limits<double>::min();
};

#endif // SENSORUNIT_H
