#ifndef COMMONVARIABLES_H
#define COMMONVARIABLES_H

#include "commonvariables_global.h"
#include <QObject>
#include <QtCore>
#include <QHash>

class COMMONVARIABLESSHARED_EXPORT CommonVariables : public QObject
{
    Q_OBJECT
    Q_ENUMS(CommandType)
    Q_ENUMS(SensorType)

public:

    enum CommandType
        {
            Q,
            C,
            R,
            S
        };

    enum SensorType {

        Temprature,

        Humid,

        Light,

        NotDefine
    };

    enum TranceiverType {

        SerialPort,

        NotDefineDevice
    };

    static CommonVariables::SensorType GetSensorKindFromUnitIndex(QString unitIndex);

    static CommonVariables::TranceiverType GetTrancieverByIndex(QString unitIndex);
};

#endif // COMMONVARIABLES_H
