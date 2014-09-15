#include "coreone.h"
#include <QtPlugin>

QString CoreOne::GetCoreName()
{
    return QString("Hi");
}

void CoreOne::CoreDataCollectBus(DataPacket data)
{

}
