#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <QMap>
#include <QString>
#include <QtSql>
//#include "irepository_global.h"

class IRepository : public QObject
{
   Q_OBJECT

public:
    IRepository();
    IRepository(QString dbName);
    ~IRepository();

    virtual bool OpenDB()=0;
    virtual bool CloseDB()=0;
    virtual bool ChangeDataBase(QString databaseName)=0;
    virtual QSqlQuery ExecuteSQLCommand(QMap<QString, QString> command)=0;

protected:

    QString dbName;
    QSqlDatabase databaseInstance;
};

Q_DECLARE_INTERFACE(IRepository, "")
#endif // IREPOSITORY_H
