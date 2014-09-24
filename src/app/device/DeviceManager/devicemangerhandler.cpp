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

bool DeviceMangerHandler::GetSensors()
{
    bool result=false;

    QString sensorConfigLocation="";

    QVariantMap jsonMap;

    QMap<QString,QVariant> controlMap, sensorMap;

    QVariantList controlBoxList, sensorList;

    if(!this->LoadConfig("config.json"))
    {
        qCritical()<<"System cannot load config.json";
        goto bye;
    }

    sensorConfigLocation = this->jsonObject["sensorconfigfile"].toString();

    qDebug() << "sensor configuration file's path:" + sensorConfigLocation;

    if(!this->LoadConfig(sensorConfigLocation))
    {
        qCritical()<<"System cannot load config.json";
        goto bye;
    }

    jsonMap = this->jsonObject.toVariantMap();

    foreach(QString value, jsonMap.keys())
    {
       controlBoxList = jsonMap[value].toList();

       foreach(QVariant controlBox, controlBoxList)
       {
          controlMap = controlBox.toMap();

          foreach(QString key, controlMap.keys())
          {
             if(key=="id")
             {
                  qDebug()<< "control box id=" + controlMap[key].toString();
             }
             else if(key=="sensors")
             {
                sensorList=controlMap[key].toList();

                foreach(QVariant sensor, sensorList)
                {
                    sensorMap=sensor.toMap();

                    foreach(QString sensorid, sensorMap.keys())
                    {
                        //qDebug()<<sensorid;
                    }
                }
             }
          }
       }
    }

    result=true;

    bye:
    return result;
}

bool DeviceMangerHandler::GetTranceievers()
{
    return false;
}

bool DeviceMangerHandler::LoadConfig(QString fileName)
{
    bool result=false;

    QDir dir(QCoreApplication::applicationDirPath());

    QFile loadFile(dir.absoluteFilePath(fileName));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file:" + fileName;
        goto bye;
    }

    this->jsonObject=QJsonDocument::fromJson(loadFile.readAll()).object();

    result=true;

    loadFile.close();

    bye:
    return result;
}
