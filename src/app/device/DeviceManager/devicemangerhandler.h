#ifndef DEVICEMANGERHANDLER_H
#define DEVICEMANGERHANDLER_H

#include "./devicemanager.h"
#include <QMap>

#include "../../sharelibs/PluginHelper/pluginhelper.h"
#include "../IDeviceFactory/idevicefactory.h"
#include "../SensorUnit/sensor.h"

class DeviceMangerHandler : public IDeviceManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{376add0a-4835-4d7a-911d-240b12454211}" FILE "info.json")
    Q_INTERFACES(IDeviceManager)

public:

    virtual bool SetCore();
    virtual bool LoadSensors();
    virtual bool LoadTranceievers();
    virtual bool LoadRepository();
    virtual QObject* GetSensors();
    virtual QObject* GetTranceievers();
    virtual bool ReleaseCore();

    QMap<QString,QMap<QString, IHardware*> > controlBox;
    QMap<QString,QMap<QString, IHardware*> > trancieverControlBox;

public slots:

  virtual void DeviceManagerCoreSlot(DataPacket data);
  virtual void DeviceManagerUISlot(DataPacket data);

private:


    ICore *core=NULL;

    QPluginLoader loader;
    QPluginLoader trancieverLoader;
    QPluginLoader repositoryLoader;
    IDeviceFactory* sensorFactory=NULL;
    IDeviceFactory* tranceiverFactory=NULL;
    IRepositoryManager* repositoryFactory=NULL;

    QJsonObject jsonObject;
    QString tranceieverLocation;
    QString sensorConfigLocation;
    QString repositoryConfigLocation;
    bool LoadConfig(QString);

    template <typename T>
    bool DisconnectCore(QMap<QString,QMap<QString, IHardware*> > *);

    template <typename T>
    bool SetupDevices(IDeviceFactory*, QMap<QString,QMap<QString, IHardware*> > *, QString, QString);
};

#endif // DEVICEMANGERHANDLER_H
