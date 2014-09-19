#ifndef PLUGINHELPER_H
#define PLUGINHELPER_H

#include "pluginhelper_global.h"
#include <QPluginLoader>
#include <QDir>
#include <QCoreApplication>

class PLUGINHELPERSHARED_EXPORT PluginHelper
{
public:
    static bool GetPlugIn(QPluginLoader& loader, QString pluginName);
};

#endif // PLUGINHELPER_H
