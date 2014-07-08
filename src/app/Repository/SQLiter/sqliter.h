#ifndef SQLITER_H
#define SQLITER_H

#include <QtSql>
#include "sqliter_global.h"
#include "../IRepository/irepository.h"

class SQLITERSHARED_EXPORT SQLiter : public IRepository
{
   Q_OBJECT

public:
    SQLiter(QString dbName);
    ~SQLiter();

    virtual bool OpenDB();
    virtual bool CloseDB();
    virtual bool ChangeDataBase(QString databaseName);
    virtual bool Execute(QHash<QString, QString> command);

private:


};

#endif // SQLITER_H
