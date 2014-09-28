#include <QApplication>
#include "html5applicationviewer.h"
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QString applicationPath=QCoreApplication::applicationDirPath();

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String(applicationPath.toLatin1() + "/html/index.html"));

    return app.exec();
}
