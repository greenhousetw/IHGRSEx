#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include <QMap>
#include "../../core/Core/core.h"
#include "../../core/Core/datapacket.h"
#include "../../Repository/IRepository/irepository.h"
#include "../../sharelibs/NotifyPackage/notifypackage.h"

class IHardware : public QObject
{
    Q_OBJECT

signals:

  void SendData(DataPacket data);

public slots:

  virtual void ReceieveData(DataPacket data)=0;
  virtual void ReceieveData(NotifyPackage data)=0;

public:

  virtual bool CoreConnector(QObject&)=0; 
  virtual bool DiconnectCoreConnector(QObject&)=0;
  virtual bool SetHardware(QMap<QString, QVariant>)=0;
  virtual bool SetRepository(IRepository*)=0;
  virtual QString GetDeviceValue()=0;
  virtual QString GetDeviceID()=0;
  virtual QString GetDeviceType()=0;
};

#endif // HARDWARE_H
