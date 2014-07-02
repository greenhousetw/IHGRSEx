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

void SensorBase::ControlHWMgrDataSlot(NotifyPackage package)
{

}
