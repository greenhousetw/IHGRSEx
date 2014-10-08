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
    Q_ENUMS(TranceiverType)


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

        AllInOne,

        NotDefine
    };

    enum TranceiverType {

        SerialPort,

        NotDefineDevice
    };



    static CommonVariables::SensorType GetSensorKindFromUnitIndex(QString unitIndex);

    static CommonVariables::TranceiverType GetTrancieverByIndex(QString unitIndex);

    static const QString IHGRSSTOPWORKING;

    static const QString TRANCIEVERHARDWARESENDMESSAGE;

    static const QString TRANCIEVERHARDWARERECEIEVEMESSAGE;

    static const QString SensorUISettingString;

    static const QString RepositoryConfigfilePath;

    static const QString RepositoryPrefix;

    static const QString SqlSelectSize;

    static const QString SqlNonSelectSize;

    static const QString SqlResult;
};

#endif // COMMONVARIABLES_H
