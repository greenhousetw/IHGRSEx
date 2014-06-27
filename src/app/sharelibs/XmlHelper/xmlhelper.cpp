#include "xmlhelper.h"

XmlHelper::XmlHelper()
{
}

/**
 * @brief XmlHelper::LoadXMLDocument
 * @param filePath
 * @return
 */
QXmlQuery* XmlHelper::LoadXMLDocument(QString filePath)
{
    QXmlQuery *query=NULL;

    QFile xmlFile(filePath);

    if(!xmlFile.exists())
    {
        qCritical()<<"file=" + filePath + " doest not exist in the system";
        qCritical()<<"Current Runtime dir=" + QDir::currentPath();
        goto orz;
    }

    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical()<<"file=" + filePath + " cannot be opened";
        goto orz;
    }

    query=new QXmlQuery(QXmlQuery::XQuery10);
    query->setFocus(&xmlFile);
    xmlFile.close();

    orz:
    return query;
}

/**
 * @brief Get values which from XPath
 * @param query
 * @param xmlPath
 * @param valueList
 * @return
 */
bool XmlHelper::GetNodeValues(QXmlQuery* query, QString xmlPath, QStringList* valueList)
{
    bool result=false;

    qDebug()<<"xml path=" + xmlPath;

    if(query == NULL)
    {
        qCritical()<<"QXmlQuery instance is NULL";
        goto orz;
    }

    query->setQuery(xmlPath);


    if(!query->isValid())
    {
        qCritical()<<"is not a valid xml path, please give the correct path";
        goto orz;
    }

    query->evaluateTo(valueList);

    qDebug()<<"xpath=" + xmlPath + " there are " + QString::number(valueList->count()) + " records";

    for(int i=0;i< valueList->count();i++)
    {
        qDebug()<<"The (" + QString::number(i+1) + ")'s value=" + valueList->at(i);
    }

    result=true;

    orz:
    return result;
}
