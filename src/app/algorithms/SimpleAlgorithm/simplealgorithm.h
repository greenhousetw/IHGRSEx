#ifndef SIMPLEALGORITHM_H
#define SIMPLEALGORITHM_H

#include <QObject>
#include <QDebug>
#include <limits>
#include <QFile>
#include <QScriptEngine>
#include "simplealgorithm_global.h"
#include "../IAlgorithm/ialgorithm.h"
#include "../../../app/sharelibs/XmlHelper/xmlhelper.h"

class SIMPLEALGORITHMSHARED_EXPORT SimpleAlgorithm : public IAlgorithm
{
    Q_OBJECT

public:
    SimpleAlgorithm();
    ~SimpleAlgorithm();
    virtual bool PreSetup();
    virtual bool ExecuteOperation(QString data);
    virtual bool StopExecution();

public slots:

    virtual void OperateDataReceiever(QString data);

private:
    QXmlQuery* xmlDoc=NULL;
    bool CheckRequirements();
    bool IsNullOrEmpty(QString key);
};

#endif // SIMPLEALGORITHM_H
