#ifndef COMMONLIB_H
#define COMMONLIB_H

#include "commonlib_global.h"
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
};

#endif // COMMONLIB_H
