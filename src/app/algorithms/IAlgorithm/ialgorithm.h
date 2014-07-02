#ifndef IALGORITHM_H
#define IALGORITHM_H

#include "ialgorithm_global.h"
#include <QHash>
#include <QObject>
#include <QVariant>
#include "../../sharelibs/CommonVariables/commonvariables.h"

class IALGORITHMSHARED_EXPORT IAlgorithm : public QObject
{
    Q_OBJECT

public:

    virtual bool PreSetup()=0;
    virtual bool ExecuteOperation()=0;
    virtual bool StopExecution()=0;

    QHash<QString, QVariant> dataStore;    

signals:

    bool EmitDeviceControlCode(QList<QString> controlCodeList);

public slots:

    virtual void OperateDataReceiever(QString data)=0;
};

#endif // IALGORITHM_H

