#include "algorithmloader.h"

void AlgorithmLoader::PrintData()
{

}

bool AlgorithmLoader::GetIAlgorithm(QString algorithmName, IAlgorithm* algorithm)
{
    bool result=false;

    QPluginLoader loader;

    qDebug()<<"Now will load alogirthm:" + algorithmName;

    if(PluginHelper::GetPlugIn(loader, algorithmName))
    {
        algorithm= qobject_cast<IAlgorithm *>(loader.instance());

        if(algorithm)
        {
            qDebug()<<"successfully loaded";
            result=true;
        }
        else
        {
            qCritical()<<"fail to load";
        }
    }

    return result;
}
