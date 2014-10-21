#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QList>
#include <QObject>
#include "../../core/Core/core.h"
#include "../../core/Core/coreone.h"
#include "../../device/Hardware/hardware.h"
#include "../Tranceiver/tranceiver.h"
#include "../../Repository/IRepositoryManager/irepositorymanager.h"
#include "../../sharelibs/CommonVariables/commonvariables.h"

class IDeviceManager : public QObject
{

    Q_OBJECT

signals:

    void DeviceManagerCoreSignal(DataPacket);
    void DeviceManagerUISignal(DataPacket);

public:

    virtual bool SetCore()=0;
    virtual bool ReleaseCore()=0;
    virtual bool LoadSensors()=0;
    virtual bool LoadTranceievers()=0;
    virtual bool LoadRepository()=0;
    virtual bool LoadAlgorithmLoader()=0;
    virtual QObject* GetSensors()=0;
    virtual QObject* GetTranceievers()=0;
    virtual QSqlQuery QueryRepository(QString)=0;

public slots:

  virtual void DeviceManagerCoreSlot(DataPacket data)=0;
  virtual void DeviceManagerUISlot(DataPacket data)=0;
};

Q_DECLARE_INTERFACE(IDeviceManager, "{4a34bcdf-1458-4d7f-ba81-f2f0fa509ae9}")

#endif // DEVICEMANAGER_H
