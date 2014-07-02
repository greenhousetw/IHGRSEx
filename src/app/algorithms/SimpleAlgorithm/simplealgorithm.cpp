/********************************************************************************************
Copyright (C) %YEAR% by IHGRS

simplealgorithm.cpp
Purpose:
To execute simple section algorithm, it configuration file is Algorithm.Simple.Setup.xml
and real jugment source is from xxx.js, which based on what profile you use.

@author Yu-Hua Tseng
@version Test.V1 07/02/2014

********************************************************************************************/
#include "simplealgorithm.h"

SimpleAlgorithm::SimpleAlgorithm()
{
    this->scriptIDKeyword="id";

    this->isChangeDevice=false;

    QMetaObject metaObject = CommonVariables::staticMetaObject;
    QMetaEnum m=metaObject.enumerator(metaObject.indexOfEnumerator("SensorType"));

     for (int i=0; i < m.keyCount(); ++i)
     {
         this->sensorTypeList.append(QString(m.valueToKey(i)));
     }         

     this->section="";
}

/**
 * @brief SimpleAlgorithm::~SimpleAlgorithm
 */
SimpleAlgorithm::~SimpleAlgorithm()
{    
}

/**
 * @brief SimpleAlgorithm::PreSetup
 * @return true for setup successfully and false for fail
 */
bool SimpleAlgorithm::PreSetup()
{
    bool result=false;

    QString algorithmSetupFile="./Algorithm.Simple.Setup.xml";

    if(this->xmlDoc==NULL)
    {
        this->xmlDoc=XmlHelper::LoadXMLDocument(algorithmSetupFile);
        result=true;
    }

    qDebug()<<"❤ " + algorithmSetupFile + " has been loaded!";
    return result;
}

/**
 * @brief SimpleAlgorithm::ExecuteOperation
 * @param data
 * @return true for successful execution and false for fail
 */
bool SimpleAlgorithm::ExecuteOperation()
{  
    bool result=false;
    QString id=this->dataStore[this->scriptIDKeyword].toString();
    QString xmlPath="//config/portfolios/set[@id=\""+id+"\"]/@script/string()";
    QString scriptFilePath="";
    QString data="";
    qDebug()<<"Read script file from xpath=" + xmlPath;

    this->PreSetup();
    this->SetSensorType(&data);

    if(!this->CheckRequirements())
    {       
        qCritical()<< "orz! Needed data cannot be setup";
        goto bye;
    }

    if(!XmlHelper::GetAttributeValueInType<QString>(xmlDoc, xmlPath,&scriptFilePath))
    {        
        qCritical()<<"too bad, get script file fail";
    }
    else
    {
        QFile scriptFile(scriptFilePath);

        if (!scriptFile.open(QIODevice::ReadOnly))
        {
            qCritical()<<"failed to open file=" + scriptFilePath;
        }
        else
        {
            try
            {
              QTextStream stream(&scriptFile);
              QString strScript;
              strScript = stream.readAll();
              scriptFile.close();
              qDebug()<<"Use id of set = " + this->dataStore[scriptIDKeyword].toString() + " sensor type=" + this->dataStore["sensortype"].toString();

              QScriptEngine jsEngine;
              QScriptValue entireJavaScript = jsEngine.evaluate(strScript);
              QScriptValue function=jsEngine.globalObject().property(this->dataStore["sensortype"].toString());
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
    }

    this->dataStore.clear();
    this->dataStore.insert(this->scriptIDKeyword, id);

    bye:
    return result;
}

/**
 * @brief ProcessScriptData
 * @param value
 * @return
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
                int diff=1;
                int passMinutes=this->lastTime.secsTo(QDateTime::currentDateTime())/diff;
                qDebug() << "pass diff time=" + QString::number(passMinutes,10) + " minuteDiff=" + QString::number(minuteDiff,10);

                if(passMinutes==minuteDiff)
                {
                    if(!this->isChangeDevice)
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
                        this->isChangeDevice=true;
                    }

                    this->lastTime=QDateTime::currentDateTime();
                }
            }
            else
            {
                this->lastTime=QDateTime::currentDateTime();
                this->section=result["section"].toString();
                this->isChangeDevice=false;
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

   delete this->xmlDoc;
   this->xmlDoc=NULL;

   return result;
}

/**
 * @brief SimpleAlgorithm::OperateDataReceiever
 * @param data
 */
void SimpleAlgorithm::OperateDataReceiever(QString data)
{


}
/**
 * @brief SimpleAlgorithm::SetSensorType
 * Get current sensor type, for trigger rleated algorithm
 */
void SimpleAlgorithm::SetSensorType(QString* data)
{
    foreach(QString key, this->dataStore.keys())
    {
        bool isSensor=false;

        foreach(QString sensor, this->sensorTypeList)
        {
            qDebug()<<"key=" + key + ", index=" + sensor;

            if(key==sensor)
            {
                this->dataStore.insert("sensortype", QVariant(sensor));
                *data=this->dataStore[key].toString();
                qDebug()<<"Value=" + this->dataStore[key].toString();
                isSensor=true;
                break;
            }
        }

        if(isSensor)
        {
            break;
        }
    }
}

/**
 * @brief SimpleAlgorithm::CheckRequirements
 * @return true for all pre requirements setup successfully and false for fail
 */
bool SimpleAlgorithm::CheckRequirements()
{
    bool result=false;

    if(this->IsNullOrEmpty(this->scriptIDKeyword))
    {
        qCritical()<<"orz, It has no script id";
        goto orz;
    }

    result=true;

    orz:
    return result;
}

/**
 * @brief SimpleAlgorithm::IsNullOrEmpty
 * @param key, which is name for data store dictionary
 * @return true for is null or empty, false for none null or empty
 */
bool SimpleAlgorithm::IsNullOrEmpty(QString key)
{
    bool result=false;

    QString data=this->dataStore[key].toString();

    if(NULL==data || 0==data.length())
    {
        qCritical()<<"orz! Requirement data:" + key + " is null or empty";
        result=true;
    }

    return result;
}
