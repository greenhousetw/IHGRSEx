#include "coreone.h"
#include <QtPlugin>
#include <QDebug>

QString CoreOne::GetCoreName()
{
    return QString("Core One");
}

void CoreOne::CoreDataCollectBus(DataPacket data)
{
    qDebug()<< "You got value=" + data.packetData.value;
}
