#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include "repositorymanager_global.h"
#include "../IRepository/irepository.h"
#include "../SQLiter/sqliter.h"

class REPOSITORYMANAGERSHARED_EXPORT RepositoryManager
{

public:
    RepositoryManager();

    enum DataBaseType{
        SQLite
    };

    bool LoadDBInstance(QString dbName, RepositoryManager::DataBaseType dbType);
    bool OpenDB();
    bool CloseDB();
    bool ChangeDataBase(QString databaseName);
    bool Execute(QHash<QString, QString> command);

private:

    IRepository* databaseInstance;
};

#endif // REPOSITORYMANAGER_H
