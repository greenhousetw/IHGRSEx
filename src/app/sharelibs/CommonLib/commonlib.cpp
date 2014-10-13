#include "commonlib.h"


CommonLib::CommonLib()
{
}

QString CommonLib::TableToJSon(QSqlQuery query)
{
    QJsonDocument  json;
    QJsonArray     recordsArray;

    while(query.next())
    {
         for(int x=0; x < query.record().count(); x++)
         {
             QJsonObject  recordObject;
             recordObject.insert( query.record().fieldName(x),
                   QJsonValue::fromVariant(query.value(x)) );
             recordsArray.push_back(recordObject);
         }
     }

    json.setArray(recordsArray);
    return json.toJson();
}
