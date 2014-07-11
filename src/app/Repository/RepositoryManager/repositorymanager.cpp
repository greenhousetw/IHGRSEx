#include "repositorymanager.h"

Q_PLUGIN_METADATA(IID "fr.inria.tstPlugin")

/**
 * @brief RepositoryManager::LoadDBInstance
 * @param dbName
 * @param dbType
 * @return
 */
bool RepositoryManager::LoadDBInstance(QString config, IRepositoryManager::DataBaseType dbType)
{
    bool result=false;

    if(dbType==IRepositoryManager::SQLite)
    {
        qDebug()<<"Current database option is SQLite";
        this->databaseInstance=new SQLiter(config);
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
