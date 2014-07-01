#include "commonvariables.h"

/**
  * @brief CommonVariables::GetSensorKindFromUnitIndex
  * return sensor kind index string, like: input=CP / FP
  * you will get temprature, if input=H, you will get humid
  * @param unitIndex
  * @return sensor kind string
  */
 CommonVariables::SensorType CommonVariables::GetSensorKindFromUnitIndex(QString unitIndex)
 {
     CommonVariables::SensorType sensorKind=CommonVariables::NotDefine;

     qDebug()<<"you get:" + unitIndex + ", now will map to";

     CommonVariables::SensorType tempratureIndex=CommonVariables::Tempratue;
     CommonVariables::SensorType humidIndex=CommonVariables::Humid;
     CommonVariables::SensorType lightIndex=CommonVariables::Light;

     QHash<QString,  CommonVariables::SensorType>  hash;
     hash.insert("CP", tempratureIndex);
     hash.insert("FP", tempratureIndex);
     hash.insert("CN", tempratureIndex);
     hash.insert("FN", tempratureIndex);
     hash.insert("H", humidIndex);
     hash.insert("A", lightIndex);
     hash.insert("B", lightIndex);

     bool isGet=false;

     foreach(QString key, hash.keys())
     {
         if(unitIndex==key)
         {
             isGet=true;
             sensorKind=hash[unitIndex];
             qDebug()<<"Map to " + key;
             break;
         }
     }

     if(!isGet)
     {
         qWarning()<<"Unknown type";
     }

     bye:
     return sensorKind;
 }
