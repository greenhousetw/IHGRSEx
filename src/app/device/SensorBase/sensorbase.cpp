/********************************************************************************************
Copyright (C) %YEAR% by IHGRS

sensorbase.cpp
Purpose:
this class is sensor based.

@author Yu-Hua Tseng
@version Test.V1 07/02/2014

********************************************************************************************/
#include "sensorbase.h"

SensorBase::SensorBase()
{
}

SensorBase::SensorBase(QString id)
{
    this->id=id;
}

SensorBase::SensorBase(QString id, CommonVariables::SensorType typeOfSensor)
{

    this->id=id;
    this->sensorType=typeOfSensor;
}

bool SensorBase::SetAlgorithm(IAlgorithm *algorithm)
{
    if(algorithm!=NULL)
    {
        this->algorithm=algorithm;
    }
    else
    {
        qCritical()<<"algorithm is NULL, we can set algorithm for the sensor";
    }
}

/**
 * @brief SensorBase::BuildHardwareInputConnection
 * To make connection between ControlHardwareManager::SignalInternalSubscribers and Sensorbase::ControlHWMgrDataSlot
 * so if ControlHardwareManager gets data from USB or any other external devices, ControlHardwareManager will emit
 * message to the slot
 * @param controlHWMgr
 * @return
 */
bool SensorBase::BuildHardwareInputConnection(ControlHardwareManager *controlHWMgr)
{
    bool result=false;

    if(controlHWMgr!=NULL)
    {
        qDebug()<<"construct connection with ControlHardwareManager for data receieving";
        connect(controlHWMgr, SIGNAL(SignalInternalSubscribers(NotifyPackage)), this, SLOT(ControlHWMgrDataSlot(NotifyPackage)));
        result=true;
    }

    return result;
}

void SensorBase::ControlHWMgrDataSlot(NotifyPackage package)
{   
}
