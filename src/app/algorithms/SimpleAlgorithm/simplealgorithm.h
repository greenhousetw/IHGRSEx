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

class SimpleAlgorithm : public IAlgorithm
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{e36e50cc-9a18-421d-af33-2402667d31c6}" FILE "info.json")
    Q_INTERFACES(IAlgorithm)

public:
    SimpleAlgorithm();
    ~SimpleAlgorithm();
    virtual bool PreSetup(QMap<QString, QVariant> initData);
    virtual bool ExecuteOperation();
    virtual bool StopExecution();

public slots:

    virtual void AlgorithmSlot(QMap<QString, QVariant> data);

private:

    QXmlQuery* xmlDoc=NULL;
    QString sensorType="";
    QString currentSetOfProfolio;
    QString section;    
    QDateTime lastTime;

    int timeDiff;
    QString idOfSet="";
    bool ProcessScriptData(QString value);
};

#endif // SIMPLEALGORITHM_H
