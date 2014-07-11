#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include <QtPlugin>
#include "repositorymanager_global.h"
#include "../IRepositoryManager/irepositorymanager.h"
#include "../IRepository/irepository.h"
#include "../SQLiter/sqliter.h"

class RepositoryManager :public QObject, public IRepositoryManager
//class REPOSITORYMANAGERSHARED_EXPORT RepositoryManager :public QObject, public IRepositoryManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IREPOSITORYINTERFAC_iid FILE "RepositoryManagerPlungIn.json")
    Q_INTERFACES(IRepositoryManager)

public:
    RepositoryManager(void) {}
    ~RepositoryManager(void) {}

    virtual bool LoadDBInstance(QString dbName, IRepositoryManager::DataBaseType dbType);
    virtual bool OpenDB();
    virtual bool CloseDB();
    virtual bool ChangeDataBase(QString databaseName);
    virtual bool Execute(QHash<QString, QString> command);

private:

    IRepository* databaseInstance;
};

#endif // REPOSITORYMANAGER_H
