#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include <QMap>
#include "../../core/Core/datapacket.h"

class IHardware : public QObject
{
    Q_OBJECT

signals:

  void SendData(DataPacket data);

public slots:

  virtual void ReceieveData(DataPacket data)=0;

public:

  virtual bool SetHardware(QMap<QString, QVariant>)=0;
  virtual QString GetDeviceValue()=0;
  virtual QString GetDeviceID()=0;
  virtual QString GetDeviceType()=0;
};

Q_DECLARE_INTERFACE(IHardware,"{51a039c6-0a1a-4eb2-9586-0941b7f8500d}")

#endif // HARDWARE_H
