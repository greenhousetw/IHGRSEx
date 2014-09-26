#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include "datapacket.h"
#include "../../sharelibs/NotifyPackage/notifypackage.h"

class ICore : public QObject
{    
    Q_OBJECT

public:

  virtual QString GetCoreName()=0;

signals:

  void CoreTrancieverBus(DataPacket data);
  void CoreSensorBus(NotifyPackage data);

public slots:

  virtual void CoreTrancieverCollectBus(DataPacket data)=0;
  virtual void CoreSensorCollectBus(DataPacket data)=0;
};

Q_DECLARE_INTERFACE(ICore,"{a1b108b3-af7e-4138-907d-55552b5d75c2}")

#endif // CORE_H
