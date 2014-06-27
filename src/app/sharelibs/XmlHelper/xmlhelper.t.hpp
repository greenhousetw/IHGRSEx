/**
 * @brief XmlHelper::GetAttributeValueInType
 * @param query
 * @param xmlPath
 * @param value
 * @return
 */
template <class T>
T XmlHelper::GetAttributeValueInType(QXmlQuery* query, QString xmlPath, T value)
{
    T *result=NULL;

    QStringList dataList;

    if(GetNodeValues(query, xmlPath, &dataList))
    {
        qDebug()<<"your data is=" + dataList[0];
        //*value=stdout::dataList[0];
        result=true;
    }

    return *result;
}
