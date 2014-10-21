#ifndef IALGORITHM_H
#define IALGORITHM_H

#include "ialgorithm_global.h"
#include <QObject>
#include <QMap>
#include "../../sharelibs/CommonVariables/commonvariables.h"

class IAlgorithm : public QObject
{
    Q_OBJECT

public:

    virtual bool PreSetup(QMap<QString, QVariant> initData)=0;
    virtual bool ExecuteOperation()=0;
    virtual bool StopExecution()=0;

signals:

    bool EmitDeviceControlCode(QList<QString> controlCodeList);

public slots:

    virtual void AlgorithmSlot(QMap<QString, QVariant> data)=0;
};

Q_DECLARE_INTERFACE(IAlgorithm, "{8a762b0f-be9c-418b-a154-e91a622ba7f3}")

#endif // IALGORITHM_H

