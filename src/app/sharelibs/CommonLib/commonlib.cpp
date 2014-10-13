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
         QJsonObject  recordObject;

         for(int x=0; x < query.record().count(); x++)
         {
             recordObject.insert( query.record().fieldName(x),
                   QJsonValue::fromVariant(query.value(x)) );
         }

         recordsArray.push_back(recordObject);
     }

    json.setArray(recordsArray);
    return json.toJson();
}
