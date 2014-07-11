#include <QApplication>
#include "html5applicationviewer.h"
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    //QStringList list;
    //list.append("./plugins");
    //app.setLibraryPaths(list);
    //QCoreApplication::setLibraryPaths(list);

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String("html/index.html"));

    return app.exec();
}
