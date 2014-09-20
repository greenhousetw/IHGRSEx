#include "coreone.h"
#include <QtPlugin>
#include <QDebug>

QString CoreOne::GetCoreName()
{
    return QString("Core One");
}

void CoreOne::CoreDataCollectBus(DataPacket data)
{
    qDebug()<< "CoreOne gets the value:" + data.packetData.value;

    emit this->CoreBus(data);
}
