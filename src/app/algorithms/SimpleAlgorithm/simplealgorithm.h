#ifndef SIMPLEALGORITHM_H
#define SIMPLEALGORITHM_H

#include <QObject>
#include <QDebug>
#include <limits>
#include <QFile>
#include <QScriptEngine>
#include <QMapNode>
#include <QJsonDocument>
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
    virtual bool ExecuteOperation();
    virtual bool StopExecution();

public slots:

    virtual void OperateDataReceiever(QString data);

private:
    QXmlQuery* xmlDoc=NULL;
    bool CheckRequirements();
    void SetSensorType(QString*);
    bool IsNullOrEmpty(QString key);
    QString scriptIDKeyword;
    QString section;
    int timeDiff;
    bool isChangeDevice;
    QList<QString> sensorTypeList;
    QDateTime lastTime;
    bool ProcessScriptData(QString value);
};

#endif // SIMPLEALGORITHM_H
