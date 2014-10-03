#include "repositorymanager.h"

Q_PLUGIN_METADATA(IID "fr.inria.tstPlugin")

/**
 * @brief RepositoryManager::LoadDBInstance
 * @param dbName
 * @param dbType
 * @return
 */
IRepository* RepositoryManager::GetRepository(QMap<QString, QVariant> configs)
{
    IRepository* repository=NULL;

    if (configs[CommonVariables::RepositoryPrefix]=="SQLiter")
    {
        repository=new SQLiter("Sqlite");
    }

    orz:
    return repository;
}
