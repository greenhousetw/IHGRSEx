#ifndef IALGORITHMFACTORY_H
#define IALGORITHMFACTORY_H

#include "../IAlgorithm/ialgorithm.h"
#include <QMap>

class IAlgorithmFactory : public QObject
{

public:   
    virtual bool GetIAlgorithm(QString algorithmName, IAlgorithm* algorithm)=0;
};

Q_DECLARE_INTERFACE(IAlgorithmFactory, "{6591d3d5-7430-4d42-84f6-7d91bb059794}")

#endif // IALGORITHMFACTORY_H
