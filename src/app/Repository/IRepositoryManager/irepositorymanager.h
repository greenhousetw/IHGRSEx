#ifndef IREPOSITORYMANAGER_H
#define IREPOSITORYMANAGER_H

#include "irepositorymanager_global.h"
#include<QHash>
#include<QObject>
#include<QtPlugin>

//class IREPOSITORYMANAGERSHARED_EXPORT IRepositoryManager
class IRepositoryManager
{

public:

    enum DataBaseType{
        SQLite
    };

    IRepositoryManager(void) {}
    virtual ~IRepositoryManager(void) {}

    virtual bool LoadDBInstance(QString dbName, IRepositoryManager::DataBaseType dbType)=0;
    virtual bool OpenDB()=0;
    virtual bool CloseDB()=0;
    virtual bool ChangeDataBase(QString databaseName)=0;
    virtual bool Execute(QHash<QString, QString> command)=0;
};

#define IREPOSITORYINTERFAC_iid "product.ihgrs.plugin.repostiory.repositoryinterface"

Q_DECLARE_INTERFACE(IRepositoryManager,IREPOSITORYINTERFAC_iid)

#endif // IREPOSITORYMANAGER_H
