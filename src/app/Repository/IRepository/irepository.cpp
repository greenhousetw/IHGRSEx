#include "irepository.h"

IRepository::IRepository()
{
}

IRepository::IRepository(QString dbName)
{
    this->dbName=dbName;
}

IRepository::~IRepository()
{
}
