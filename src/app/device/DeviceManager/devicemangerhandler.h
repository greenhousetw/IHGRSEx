#ifndef DEVICEMANGERHANDLER_H
#define DEVICEMANGERHANDLER_H

#include "./devicemanager.h"

class DeviceMangerHandler : public IDeviceManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{376add0a-4835-4d7a-911d-240b12454211}" FILE "info.json")
    Q_INTERFACES(IDeviceManager)

public:

    virtual bool SetCore();
    virtual bool LoadSensors();
    virtual bool LoadTranceievers();
    virtual QList<IHardware*> GetSensors();
    virtual QList<IHardware*> GetTranceievers();

private:


    ICore *core=NULL;

    QList<IHardware*> sensorList;
    QList<IHardware*> tranceieverList;

    QJsonObject sensorconfigJson;
    QString sensorConfigLocation;
    bool LoadConfig(QString);
};

#endif // DEVICEMANGERHANDLER_H
