#ifndef PLUGINHELPER_H
#define PLUGINHELPER_H

#include "pluginhelper_global.h"
#include <QPluginLoader>
#include <QDir>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class PLUGINHELPERSHARED_EXPORT PluginHelper
{
public:
    static bool GetPlugIn(QPluginLoader& loader, QString pluginName);
    static bool GetJSON(QString fileName, QJsonObject* jsonDocument);
};

#endif // PLUGINHELPER_H
