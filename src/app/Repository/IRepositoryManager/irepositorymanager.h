#ifndef IREPOSITORYMANAGER_H
#define IREPOSITORYMANAGER_H

#include "irepositorymanager_global.h"
#include<QObject>
#include<QtPlugin>
#include "../IRepository/irepository.h"

class IRepositoryManager : public QObject
{

public:

    virtual IRepository* GetRepository(QMap<QString, QVariant> configs)=0;
};

Q_DECLARE_INTERFACE(IRepositoryManager,"{666060F9-40E5-4118-A9B4-587E92C132B7}")

#endif // IREPOSITORYMANAGER_H
