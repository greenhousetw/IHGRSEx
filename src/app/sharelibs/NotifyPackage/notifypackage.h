#ifndef NOTIFYPACKAGE_H
#define NOTIFYPACKAGE_H

#include "notifypackage_global.h"
#include <QHash>
#include <QtCore>
#include <QObject>
#include "../CommonVariables/commonvariables.h"

class NOTIFYPACKAGESHARED_EXPORT NotifyPackage
{

public:

    NotifyPackage();

    QString target="";
    QString info="empty";
    CommonVariables::CommandType commandType=CommonVariables::Q;
    QHash<QString, QString> notificationContent;

};

#endif // NOTIFYPACKAGE_H
