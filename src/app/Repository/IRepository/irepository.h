#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <QHash>
#include <QString>
#include <QtSql>
#include "irepository_global.h"

class IREPOSITORYSHARED_EXPORT IRepository : public QObject
{
   Q_OBJECT

public:
    IRepository();
    IRepository(QString dbName);
    ~IRepository();

    virtual bool OpenDB()=0;
    virtual bool CloseDB()=0;
    virtual bool ChangeDataBase(QString databaseName)=0;
    virtual bool Execute(QHash<QString, QString> command)=0;

protected:

    QString dbName;
    QSqlDatabase databaseInstance;
};

#endif // IREPOSITORY_H
