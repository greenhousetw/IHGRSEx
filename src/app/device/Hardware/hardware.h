#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include "../../core/Core/datapacket.h"

class IHardware : public QObject
{
    Q_OBJECT

signals:

  void SendData(DataPacket data);

public slots:

  virtual void ReceieveData(DataPacket data)=0;
};

//Q_DECLARE_INTERFACE(IHardware,"IHardware")

#endif // HARDWARE_H
