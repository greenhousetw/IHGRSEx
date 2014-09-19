#include "pluginhelper.h"

bool PluginHelper::GetPlugIn(QPluginLoader& loader, QString pluginName)
{
    bool result=false;

    QDir pluginsDir(qApp->applicationDirPath());

    const QString OSWINDebugDir="debug";
    const QString OSWINReleaseDir="release";

    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == OSWINDebugDir || pluginsDir.dirName().toLower() == OSWINReleaseDir)
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
    #endif
        pluginsDir.cd("plugins");

    pluginsDir.cd(OSWINDebugDir);

    loader.setFileName(pluginsDir.absoluteFilePath(pluginName));

    if (loader.instance()) {
        result=true;
    }

    return result;
}
