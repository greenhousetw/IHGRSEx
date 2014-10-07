#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include <QtPlugin>
#include "repositorymanager_global.h"
#include "../IRepositoryManager/irepositorymanager.h"
#include "../IRepository/irepository.h"
#include "../SQLiter/sqliter.h"
#include "../../sharelibs/PluginHelper/pluginhelper.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class RepositoryManager : public IRepositoryManager
{   
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{943B47E7-FF39-4E0B-BCDF-C3D1FB4CB15B}" FILE "RepositoryManagerPlungIn.json")
    Q_INTERFACES(IRepositoryManager)

public:

    virtual IRepository* GetRepository(QMap<QString, QVariant> configs);

private:


};

#endif // REPOSITORYMANAGER_H
