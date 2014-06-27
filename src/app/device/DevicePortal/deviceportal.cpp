#include "deviceportal.h"


DevicePortal::DevicePortal()
{
}

DevicePortal::~DevicePortal()
{
    this->ClearSensorList();
}

bool DevicePortal::InitializeSensors()
{
    bool result=false;



    return result;
}

bool DevicePortal::MakeSensorControlHWManagerConnection()
{
    bool result=false;

    try
    {
        qDebug()<<"Sensor count=" + this->sensorlist.count();

        foreach(QString id, this->sensorlist.keys())
        {
            SensorBase *sensor=this->sensorlist[id];
            connect(&this->controlHWManager, SIGNAL(ControlHardwareManager::SignalInternalSubscribers), sensor, SLOT(SensorBase::ControlHWMgrDataSlot));
        }

        result=true;
    }
    catch(std::exception &e)
    {
        qCritical()<<e.what();
    }

    return result;
}

 bool DevicePortal::ClearSensorList()
 {
     foreach(QString id, this->sensorlist.keys())
     {
        SensorBase *sensor=this->sensorlist[id];

        if(sensor!=NULL)
        {
            delete sensor;
            sensor=NULL;
        }
     }
 }
