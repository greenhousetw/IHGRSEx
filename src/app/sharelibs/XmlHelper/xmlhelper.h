#ifndef XMLHELPER_H
#define XMLHELPER_H

#include "xmlhelper_global.h"
#include <QDebug>
#include <QFile>
#include <QtXmlPatterns/QXmlQuery>
#include <QXmlResultItems>
#include <QXmlNodeModelIndex>
#include <QDir>
#include <QVariant>

class XMLHELPERSHARED_EXPORT XmlHelper
{

public:
    XmlHelper();

    static QXmlQuery* LoadXMLDocument(QString filePath);
    static bool GetNodeValues(QXmlQuery* query, QString xmlPath, QStringList* valueList);

    /**
     * Get attribute value in given data type
     */
    template<class T>
    static bool GetAttributeValueInType(QXmlQuery* query, QString xmlPath, T *value)
    {
        bool result=false;

        QStringList dataList;

        if(GetNodeValues(query, xmlPath, &dataList))
        {
            qDebug()<<"your data is=" + dataList[0];
            QVariant variant(dataList[0]);
            *value= variant.value<T>();
            result=true;
        }

        return result;
    }
};

#endif // XMLHELPER_H
