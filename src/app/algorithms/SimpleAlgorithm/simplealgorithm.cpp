#include "simplealgorithm.h"

SimpleAlgorithm::SimpleAlgorithm()
{

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

    this->xmlDoc=XmlHelper::LoadXMLDocument(algorithmSetupFile);

    if(xmlDoc != NULL)
    {
        qDebug()<<"❤ " + algorithmSetupFile + " has been loaded!";
        result=true;
    }
    else
    {
        qCritical()<<"orz! there is no " + algorithmSetupFile + " in the system";
    }

    return result;
}

/**
 * @brief SimpleAlgorithm::ExecuteOperation
 * @param data
 * @return true for successful execution and false for fail
 */
bool SimpleAlgorithm::ExecuteOperation(QString data)
{  
    bool result=false;

    QString id=this->dataStore["id"].toString();
    QString xmlPath="//config/portfolios/set[@id=\""+id+"\"]/@script/string()";
    QString scriptFilePath="";

    qDebug()<<"Read script file from xpath=" + xmlPath;

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

              qDebug()<<"Use id of set = " + this->dataStore["id"].toString() + " sensor type=" + this->dataStore["sensortype"].toString();
              qDebug()<<"Data = " + data;
              QScriptEngine jsEngine;
              QScriptValue entireJavaScript = jsEngine.evaluate(strScript);
              QScriptValue function=jsEngine.globalObject().property(this->dataStore["sensortype"].toString());
              QScriptValueList args;
              args << QScriptValue(data);
              qDebug()<<"Script returns value=" + function.call(QScriptValue(), args).toString();

              result=true;
            }
            catch(const QString& msg)
            {
                qCritical()<< "orz!" + msg;
            }
        }
    }

    bye:
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
 * @brief SimpleAlgorithm::CheckRequirements
 * @return true for all pre requirements setup successfully and false for fail
 */
bool SimpleAlgorithm::CheckRequirements()
{
    bool result=false;

    if(this->IsNullOrEmpty("id"))
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
