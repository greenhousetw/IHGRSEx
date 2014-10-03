#include "commonvariables.h"

const QString CommonVariables::IHGRSSTOPWORKING="IHGRSSTOPWORKING";
const QString CommonVariables::TRANCIEVERHARDWARESENDMESSAGE="TRANCIEVERHARDWARESENDMESSAGE";
const QString CommonVariables::TRANCIEVERHARDWARERECEIEVEMESSAGE="TRANCIEVERHARDWARERECEIEVEMESSAGE";
const QString CommonVariables::SensorUISettingString="SensorUISetting";
const QString CommonVariables::RepositoryConfigfilePath="RepositoryConfig.json";
const QString CommonVariables::RepositoryPrefix="RepositoryPrefix";
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

     CommonVariables::SensorType tempratureIndex=CommonVariables::Temprature;
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
             qDebug()<< key + " maps to sensor type successfully";
             break;
         }
     }

     if(!isGet)
     {
         //qWarning()<<"Unknown type";
     }

     bye:
     return sensorKind;
 }



 /**
   * @brief CommonVariables::GetSensorKindFromUnitIndex
   * return sensor kind index string, like: input=CP / FP
   * you will get temprature, if input=H, you will get humid
   * @param unitIndex
   * @return tranciever kind string
   */
 CommonVariables::TranceiverType CommonVariables::GetTrancieverByIndex(QString unitIndex)
 {
     CommonVariables::TranceiverType trancieverKind=CommonVariables::NotDefineDevice;

     CommonVariables::TranceiverType serialPort=CommonVariables::SerialPort;

     QHash<QString,  CommonVariables::TranceiverType>  hash;
     hash.insert("SerialPort", serialPort);

     bool isGet=false;

     foreach(QString key, hash.keys())
     {
         if(unitIndex==key)
         {
             isGet=true;
             trancieverKind=hash[unitIndex];
             qDebug()<< key + " maps to tranceiver type successfully";
             break;
         }
     }

     if(!isGet)
     {
         qWarning()<<"Unknown type";
     }

     bye:
     return trancieverKind;
 }
