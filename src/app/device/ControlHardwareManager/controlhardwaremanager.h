#ifndef CONTROLHARDWAREMANAGER_H
#define CONTROLHARDWAREMANAGER_H

#include "controlhardwaremanager_global.h"
#include <QObject>
#include <QHash>
#include <QVariant>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QScriptEngine>
#include <QException>
#include <QMetaEnum>
#include "../../sharelibs/NotifyPackage/notifypackage.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class CONTROLHARDWAREMANAGERSHARED_EXPORT ControlHardwareManager : public QObject
{
    Q_OBJECT

public:
    ControlHardwareManager();

    enum SupportCommandType{
        gethardwareCtype,
        gethardwareQtype,
        gethardwareRtype,
        gethardwareStype
    };

    Q_ENUMS(SupportCommandType)

    ControlHardwareManager::SupportCommandType commandType=ControlHardwareManager::gethardwareQtype;

signals:

    void SignalHardwareDevices(QHash<QString,QVariant> controlTable);
    void SignalInternalSubscribers(NotifyPackage package);

public slots:

    void CommandSlotRSQ(QHash<QString, QString> nodeHash);
    void CommandSlotC(QList<QString> machineStatusList);
    void PassDataToHardwareDevice(QString data);
    void HardwareReceieverSlot(QString bundlData);

private:

    QScriptEngine jsEngine;
    QString strScript;

    QString GetParityString();

    bool ParseHardwareInputDataStream(QString dataStream);
    bool EncapsulatePackage(QString data);
};

#endif // CONTROLHARDWAREMANAGER_H
