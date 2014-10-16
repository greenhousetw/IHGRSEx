#ifndef COMMONLIB_H
#define COMMONLIB_H

#include "commonlib_global.h"
#include <QDebug>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlRecord>
#include <QVariant>

class COMMONLIBSHARED_EXPORT CommonLib
{

public:
    CommonLib();

    static QString TableToJSon(QSqlQuery query);
    static QVariantMap ParseJSon(QString);
};

#endif // COMMONLIB_H
