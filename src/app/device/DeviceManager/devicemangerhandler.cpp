#include "devicemangerhandler.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>


bool DeviceMangerHandler::SetCore()
{
    bool result=false;

    return result;
}

bool DeviceMangerHandler::LoadSensors()
{
    bool result=false;

    QString sensorConfigs="./config.json";

    this->LoadConfig(sensorConfigs);


    return result;
}

bool DeviceMangerHandler::LoadTranceievers()
{
    bool result=false;

    return result;
}

QList<IHardware*> DeviceMangerHandler::GetSensors()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());

    QString sensorConfigs=pluginsDir.absoluteFilePath("config.json");

    qDebug()<<"Sensor config file=" + sensorConfigs;

    if(this->LoadConfig(sensorConfigs))
    {
        QString sensorConfigLocation = this->sensorconfigJson["sensorconfigfile"].toString();

        qDebug() << sensorConfigLocation;
    }

    return this->sensorList;
}

QList<IHardware*> DeviceMangerHandler::GetTranceievers()
{
    return this->tranceieverList;
}

bool DeviceMangerHandler::LoadConfig(QString fileName)
{
    bool result=false;

    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }
    else
    {
        this->sensorconfigJson=QJsonDocument::fromJson(loadFile.readAll()).object();
        result=true;
    }

    loadFile.close();
    return result;
}
