#include "devicemangerhandler.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

bool DeviceMangerHandler::SetCore()
{
    bool result=false;          

    this->ReleaseCore();

    if(!this->LoadConfig("config.json"))
    {
        qCritical()<<"System cannot load config.json";
        goto orz;
    }

    if (!PluginHelper::GetPlugIn(this->repositoryLoader, this->jsonObject["repositoryloader"].toString()))
    {
      qCritical()<<"system cannot load:" + this->jsonObject["repositoryloader"].toString();
      goto orz;
    }

    if (!PluginHelper::GetPlugIn(this->loader, this->jsonObject["sensorloader"].toString()))
    {
      qCritical()<<"system cannot load:" + this->jsonObject["sensorloader"].toString();
      goto orz;
    }

    if (!PluginHelper::GetPlugIn(this->trancieverLoader, this->jsonObject["tranceiverloader"].toString()))
    {
      qCritical()<<"system cannot load:" + this->jsonObject["tranceiverloader"].toString();
      goto orz;
    }      

    // Create repository, sensor and tranciever factory
    this->repositoryFactory= qobject_cast<IRepositoryManager *>(this->repositoryLoader.instance());
    this->sensorFactory = qobject_cast<IDeviceFactory *>(this->loader.instance());
    this->tranceiverFactory = qobject_cast<IDeviceFactory *>(this->trancieverLoader.instance());

    // Get configuration file's location
    this->repositoryConfigLocation = this->jsonObject["repositoryconfigfile"].toString();
    this->tranceieverLocation= this->jsonObject["tranceieverconfigfile"].toString();
    this->sensorConfigLocation = this->jsonObject["sensorconfigfile"].toString();

    qDebug()<<"the location of repository configuration file=" + this->repositoryConfigLocation;
    qDebug()<<"the location of sensor configuration file=" + this->sensorConfigLocation;
    qDebug()<<"the location of tranciever configuration file=" + this->tranceieverLocation;

    // Initialize Core
    this->core=new CoreOne;
    connect(this, SIGNAL(DeviceManagerCoreSignal(DataPacket)), this->core, SLOT(CoreDeviceManagerCollectionBus(DataPacket)));
    connect(this->core, SIGNAL(CoreDeviceManagerSignal(DataPacket)), this, SLOT(DeviceManagerCoreSlot(DataPacket)));

    result=true;

    qDebug()<<"Core set successfully";
    orz:
    return result;
}

bool DeviceMangerHandler::ReleaseCore()
{
    bool result=false;

    if(this->core)
    {
        this->DisconnectCore<Sensor>(&this->controlBox);
        this->DisconnectCore<Tranceiver>(&this->trancieverControlBox);

        delete this->core;
        this->core=NULL;
    }

    if(this->loader.isLoaded())
    {
        this->loader.unload();
    }

    if(this->trancieverLoader.isLoaded())
    {
        trancieverLoader.unload();
    }

    if(this->repositoryLoader.isLoaded())
    {
        this->repositoryLoader.unload();
    }

    if(this->sensorFactory)
    {
        delete this->sensorFactory;
        this->sensorFactory=NULL;
    }

    if(this->tranceiverFactory)
    {
        delete this->tranceiverFactory;
        this->tranceiverFactory=NULL;
    }

    if(this->repositoryFactory)
    {
        delete this->repositoryFactory;
        this->repositoryFactory=NULL;
    }

    result=true;

    return result;
}

bool DeviceMangerHandler::LoadSensors()
{
    bool result=this->SetupDevices<Sensor>(this->sensorFactory, &this->controlBox,
                       this->sensorConfigLocation, "sensors");

    if(result)
    {
        qDebug()<<" count of sensor ControlBox=" + QString::number(this->controlBox.count());
    }

    return result;
}

bool DeviceMangerHandler::LoadRepository()
{
    bool result=false;

    QJsonObject jsonRepo;
    QMap<QString, QVariant> config;

    if(!PluginHelper::GetJSON(this->repositoryConfigLocation,&jsonRepo))
    {
        qCritical()<<"Cannnot load repository config file:" + this->repositoryConfigLocation;
        goto orz;
    }

    config.insert(CommonVariables::RepositoryPrefix,jsonRepo["repository"].toString());

    this->repository=this->repositoryFactory->GetRepository(config);

    if(this->repository==NULL)
    {
        qCritical()<<"Cannnot load repository:" + config[CommonVariables::RepositoryPrefix].toString();
        goto orz;
    }

    this->repository->ChangeDataBase(jsonRepo["dbName"].toString());

    result=true;

    orz:
    return result;
}

bool DeviceMangerHandler::LoadTranceievers()
{
    bool result=this->SetupDevices<Tranceiver>(this->tranceiverFactory, &this->trancieverControlBox,
                       this->tranceieverLocation, "tranciever");

    if(result)
    {
        qDebug()<<" count of Tranciever ControlBox=" + QString::number(this->trancieverControlBox.count());
    }

    return result;
}

bool DeviceMangerHandler::LoadAlgorithmLoader()
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

void DeviceMangerHandler::DeviceManagerCoreSlot(DataPacket data)
{
    if(data.packetData.payload.toString()==CommonVariables::SensorUISettingString)
    {
        emit this->DeviceManagerUISignal(data);
    }
}

void DeviceMangerHandler::DeviceManagerUISlot(DataPacket data)
{
   QVariantMap valueMap=CommonLib::ParseJSon(data.packetData.value);

   foreach(QString key, valueMap.keys())
   {
     QString keyContent=valueMap[key].toString();

     if(keyContent==CommonVariables::FakeSensorRequest || keyContent==CommonVariables::HWRequest)
     {
         emit this->DeviceManagerCoreSignal(data);        
     }    
   }
}

QObject* DeviceMangerHandler::GetSensors()
{
    return NULL;
}

QObject* DeviceMangerHandler::GetTranceievers()
{
   return NULL;
}

QSqlQuery DeviceMangerHandler::QueryRepository(QString sqlString)
{
    QSqlQuery query;

    QMap<QString, QString> command;
    command.insert("UIQuery", sqlString);

    return this->repository->ExecuteSQLCommand(command);
}

template <typename T>
bool DeviceMangerHandler::DisconnectCore(QMap<QString,QMap<QString, IHardware*> > *controlBox)
{
    foreach(QString id, controlBox->keys())
    {
        QMap<QString, IHardware*> record= controlBox->value(id);

        foreach (QString sid, record.keys())
        {
            T* device=(T*) record[sid];
            device->DiconnectCoreConnector(*this->core);
        }
    }
}

template <typename T>
bool DeviceMangerHandler::SetupDevices(IDeviceFactory* factory, QMap<QString,QMap<QString, IHardware*> > *controlBoxInstance, QString configurationFile, QString loadType)
{
    bool result=false;

    QVariantMap jsonMap;

    QMap<QString,QVariant> controlMap, innerDeviceMap;

    QVariantList boxList, innerDeviceList;

    if(this->jsonObject.count()==0)
    {
        qWarning()<<"Please execute SetCore first";
        goto bye;
    }

    qDebug() << "configuration file's path:" + configurationFile;

    if(!this->LoadConfig(configurationFile))
    {       
        goto bye;
    }

    jsonMap = this->jsonObject.toVariantMap();

    foreach(QString value, jsonMap.keys())
    {
       boxList = jsonMap[value].toList();

       foreach(QVariant controlBox, boxList)
       {
          controlMap = controlBox.toMap();

          QMap<QString, IHardware*> internalDeviceSet;

          foreach(QString key, controlMap.keys())
          {
             if(key==loadType)
             {
                innerDeviceList=controlMap[key].toList();

                QMap<QString, QVariant> info;

                foreach(QVariant innerDevice, innerDeviceList)
                {
                    innerDeviceMap=innerDevice.toMap();

                    QString id="id";
                    QString type="type";
                    QString controlboxId="controlBoxid";
                    QString algorithmString="algorithm";

                    info.insert(id, QVariant(innerDeviceMap[id].toString()));
                    info.insert(type, QVariant(innerDeviceMap[type].toString()));
                    info.insert(controlboxId, QVariant(innerDeviceMap[controlboxId].toString()));

                    if(innerDeviceMap.contains(algorithmString))
                    {
                        info.insert(algorithmString, QVariant(innerDeviceMap[algorithmString].toString()));
                    }

                    T* deviceObject = (T*) factory->GetDevice(info);
                    deviceObject->CoreConnector(*this->core);
                    deviceObject->SetRepository(this->repository);
                    deviceObject->SetHardware(info);
                    internalDeviceSet.insert(innerDeviceMap[id].toString(), deviceObject);
                    info.clear();
                }

                controlBoxInstance->insert(controlMap["controlboxid"].toString(), internalDeviceSet);
             }
          }
       }
    }

    result=true;

    qDebug()<<"Size of ControlBox set=" + QString::number(controlBoxInstance->count());

    bye:
    return result;
}
