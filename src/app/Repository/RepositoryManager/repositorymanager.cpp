#include "repositorymanager.h"


RepositoryManager::RepositoryManager()
{
}

bool RepositoryManager::LoadDBInstance(QString dbName, RepositoryManager::DataBaseType dbType)
{
    bool result=false;

    if(dbType==RepositoryManager::SQLite)
    {
        this->databaseInstance=new SQLiter(dbName);
    }

    result=true;

    return result;
}

bool RepositoryManager::OpenDB()
{
    return this->databaseInstance->OpenDB();
}

bool RepositoryManager::CloseDB()
{
    return this->databaseInstance->CloseDB();
}

bool RepositoryManager::ChangeDataBase(QString databaseName)
{
    return this->databaseInstance->ChangeDataBase(databaseName);
}

bool RepositoryManager::Execute(QHash<QString, QString> command)
{
    return this->databaseInstance->Execute(command);
}
