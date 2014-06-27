#ifndef DEVICEBASE_H
#define DEVICEBASE_H

#include "devicebase_global.h"
#include <QString>
#include <QHash>
#include <QObject>

class DEVICEBASESHARED_EXPORT DeviceBase : public QObject
{
    Q_OBJECT

public:
    DeviceBase();

signals:

    void SingalToSubscribers(QHash<QString, QString> data);

protected:

    QString id="";
    double  value;
};

#endif // DEVICEBASE_H
