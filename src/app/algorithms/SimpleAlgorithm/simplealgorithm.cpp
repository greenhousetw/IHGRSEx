/********************************************************************************************
Copyright (C) %YEAR% by Yu-Hua Tseng

simplealgorithm.cpp
Purpose:
To execute simple section algorithm, it configuration file is Algorithm.Simple.Setup.xml
and real jugment source is from xxx.js, which based on what profile you use.

@author Yu-Hua Tseng
@version Test.V1 07/02/2014

********************************************************************************************/
#include "simplealgorithm.h"

/**
 * @brief Constructor of SimpleAlgorithm
 */
SimpleAlgorithm::SimpleAlgorithm()
{      
}

/**
 * @brief Deconstructor of SimpleAlgorithm
 */
SimpleAlgorithm::~SimpleAlgorithm()
{    
}

/*!
 * @brief  to initialize algorithm
 * @return use boolean value to indicate initialization result
 * @retval true or false
 * @author Yu-Hua Tseng
 * @date 2014/10/21
 */
bool SimpleAlgorithm::PreSetup(QMap<QString, QVariant> initData)
{
    bool result=false;

    QString algorithmSetupFile="./Algorithm.Simple.Setup.xml";

    int retryTimes=5;

    if(initData.size()==0 || initData[CommonVariables::SensorTypeString].toString().length()==0)
    {
        qCritical()<<"orz! There is no any data for initialization";
        goto orz;
    }

    this->sensorType=initData[CommonVariables::SensorTypeString].toString();

    qDebug()<<"This algorithm is for sensor type=" + this->sensorType;

    while(retryTimes > 0)
    {
        this->xmlDoc=XmlHelper::LoadXMLDocument(algorithmSetupFile);

        if(this->xmlDoc)
        {
            qDebug()<<"❤ " + algorithmSetupFile + " has been loaded!";
            result=true;
            break;
        }

        retryTimes--;
    }

    if(!result)
    {
        qCritical()<<":( " + algorithmSetupFile + " fail load algorithm setting file:" + algorithmSetupFile;
        goto orz;
    }

    orz:
    return result;
}

/**
 * @brief SimpleAlgorithm::OperateDataReceiever
 * @param data
 */
void SimpleAlgorithm::AlgorithmSlot(QMap<QString, QVariant> data)
{
    foreach(QString key, data.keys())
    {
        if(key==CommonVariables::SensorIncomingValue)
        {

        }
    }
}

/*!
 * @brief  to start algorithm execution
 * @return use boolean value to indicate initialization result
 * @retval true or false
 * @author Yu-Hua Tseng
 * @date 2014/10/21
 */
bool SimpleAlgorithm::ExecuteOperation()
{  
    bool result=false;

    QString xPathForProfolio[]={"//config/portfolios/@useSet/string()","//config/portfolios/set[@id=\""+this->currentSetOfProfolio+"\"]/@script/string()"};
    QString useSet="", scriptFilePath="", data="", strScript="";

    // To get current using set
    if(XmlHelper::GetAttributeValueInType<QString>(xmlDoc, xPathForProfolio[0],&useSet) && (useSet.length()!=0))
    {
        // to get real algorithm java script  of current using set
        if(XmlHelper::GetAttributeValueInType<QString>(xmlDoc, xPathForProfolio[1],&scriptFilePath) && (scriptFilePath.length()!=0))
        {
            qDebug()<<"Use Algorithm.Simple.Setup.xml's xpath=" + scriptFilePath + " to locate execution script";

            QFile scriptFile(scriptFilePath);

            // open xxx.js, which xxx is real algorithm name
            if (scriptFile.open(QIODevice::ReadOnly))
            {
                try
                {

                  QTextStream stream(&scriptFile);
                  strScript = stream.readAll();
                  scriptFile.close();

                  QScriptEngine jsEngine;
                  QScriptValue entireJavaScript = jsEngine.evaluate(strScript);
                  QScriptValue function=jsEngine.globalObject().property(this->sensorType);
                  QScriptValueList args;
                  args << QScriptValue(data);
                  QString scriptReturnValue=function.call(QScriptValue(), args).toString();
                  qDebug()<<"Script returns value=" + scriptReturnValue;
                  result=this->ProcessScriptData(scriptReturnValue);
                }
                catch(const QString& msg)
                {
                    qCritical()<< "orz!" + msg;
                }
            }
            else
            {
                qCritical()<<"failed to open file=" + scriptFilePath;
            }
        }
        else
        {
            qCritical()<<"orz! get script file fail";
        }
    }
    else
    {
        qCritical()<<"orz! get current using set fail";
    }

    return result;
}

/*!
 * @brief  to initialize sensor internal data
 * @param  this collection stores values, which has id, controlBoxid
 * @return use boolean value to indicate initialization result
 * @retval true or false
 * @author Yu-Hua Tseng
 * @date 2014/07/01
 */
bool SimpleAlgorithm::ProcessScriptData(QString value)
{
    bool result=false;

    QJsonParseError error;
    QJsonDocument jsonDocument  = QJsonDocument::fromJson(value.toUtf8(), &error);

    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument .isObject()) {

            QVariantMap result = jsonDocument.toVariant().toMap();
            qDebug() << "section:" << result["section"].toString();

            if(this->section==result["section"].toString())
            {
                qDebug() << "reach alram section";

                bool ok=false;
                int minuteDiff=result["minuteDiff"].toString().toInt(&ok, 10);
                int diff=result["unitseconds"].toString().toInt(&ok, 10);
                int passMinutes=this->lastTime.secsTo(QDateTime::currentDateTime())/diff;
                qDebug() << "pass diff time=" + QString::number(passMinutes,10) + " minuteDiff=" + QString::number(minuteDiff,10);

                if(passMinutes==minuteDiff)
                {
                  qDebug() << "---------------------------change device's status---------------------------";
                  QList<QString> machinestatus;
                  foreach (QVariant device, result["equipments"].toList())
                  {
                      QMap<QString, QVariant> deviceNode=device.toMap();
                      qDebug()<<"Device=" + deviceNode.keys()[0]+  ", status=" + deviceNode[deviceNode.keys()[0]].toString();
                      machinestatus.append(deviceNode[deviceNode.keys()[0]].toString());
                  }
                  emit this->EmitDeviceControlCode(machinestatus);
                  qDebug() << "---------------------------------------------------------------------------";
                  this->lastTime=QDateTime::currentDateTime();
                }
            }
            else
            {
                this->lastTime=QDateTime::currentDateTime();
                this->section=result["section"].toString();                
            }

            /*QString format = "ddd,dd MMM yyyy HH:mm:ss";
            QLocale loc = QLocale(QLocale::English, QLocale::UnitedStates);
            QDateTime t = QDateTime::currentDateTime();
            QString timeString=loc.toString( t, format);*/
        }

        result=true;

    } else {
        qFatal(error.errorString().toUtf8().constData());
    }

    return result;
}

/**
 * @brief SimpleAlgorithm::StopExecution
 * @return true for successful stop executing and false for fail
 */
bool SimpleAlgorithm::StopExecution()
{
   bool result=false;

   if(this->xmlDoc)
   {
       delete this->xmlDoc;
       this->xmlDoc=NULL;
   }

   result=true;

   return result;
}
