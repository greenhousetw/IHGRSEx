#ifndef DEVICEMANGERHANDLER_H
#define DEVICEMANGERHANDLER_H

#include "./devicemanager.h"
#include <QMap>

class DeviceMangerHandler : public IDeviceManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{376add0a-4835-4d7a-911d-240b12454211}" FILE "info.json")
    Q_INTERFACES(IDeviceManager)

public:

    virtual bool SetCore();
    virtual bool LoadSensors();
    virtual bool LoadTranceievers();
    virtual bool GetSensors();
    virtual bool GetTranceievers();

private:


    ICore *core=NULL;

    QMap<QString,QMap<QString, IHardware*> > controlBox;
    QList<IHardware*> tranceieverList;
    QJsonObject jsonObject;
    QString sensorConfigLocation;
    bool LoadConfig(QString);
};

#endif // DEVICEMANGERHANDLER_H
