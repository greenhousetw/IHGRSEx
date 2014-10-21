#ifndef ALGORITHMLOADER_H
#define ALGORITHMLOADER_H

#include "../IAlgorithmFactory/ialgorithmfactory.h"
#include "../../sharelibs/PluginHelper/pluginhelper.h"

class AlgorithmLoader : public IAlgorithmFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "{a01b0832-6ae8-4995-8875-d70c4d7395dd}" FILE "info.json")
    Q_INTERFACES(IAlgorithmFactory)

public:

    virtual bool GetIAlgorithm(QString algorithmName, IAlgorithm* algorithm);

private:
     void PrintData();
};

#endif // ALGORITHMLOADER_H
