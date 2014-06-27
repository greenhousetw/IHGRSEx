#ifndef COMMONVARIABLES_H
#define COMMONVARIABLES_H

#include "commonvariables_global.h"
#include <QObject>
#include <QtCore>

class COMMONVARIABLESSHARED_EXPORT CommonVariables : public QObject
{
    Q_OBJECT
    Q_ENUMS(CommandType)

public:

    enum CommandType
        {
            Q,
            C,
            R,
            S
        };

    enum SensorType {

        Tempratue,

        Humid,

        Light,

        NotDefine
    };
};

#endif // COMMONVARIABLES_H
