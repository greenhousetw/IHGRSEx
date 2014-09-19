#ifndef IDEVICEFACTORY_H
#define IDEVICEFACTORY_H

#include <QObject>
#include <QMap>
#include "../Hardware/hardware.h"

class IDeviceFactory : public QObject
{

public:

    virtual IHardware* GetDevice(QMap<QString, QVariant>)=0;
};

Q_DECLARE_INTERFACE(IDeviceFactory, "{f45fcfa9-5ab5-4842-9c0b-46f8e2754277}")

#endif // IDEVICEFACTORY_H
