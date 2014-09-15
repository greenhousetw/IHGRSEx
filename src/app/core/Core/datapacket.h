#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <QObject>
#include <QVariant>

class DataPacket
{

private:

    struct dataStructure
    {
        QString  id;
        QString  value;
        QVariant payload;
    };

public:

   dataStructure packetData;
};

#endif // DATAPACKET_H
