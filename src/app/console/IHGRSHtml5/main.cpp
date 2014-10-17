#include <QApplication>
#include "html5applicationviewer.h"
#include <QDebug>
#include <QDir>
#include <QMutex>
#include <QDateTime>
#include <QMessageLogger>

QString applicationPath="";
QMutex mutex;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    bool isAbort=false;

    mutex.lock();

    QString logType;

    switch (type)
    {
        case QtDebugMsg:
            logType = QString("Debug:");
            break;
        case QtWarningMsg:
            logType = QString("Warning:");
            break;
        case QtCriticalMsg:
            logType = QString("Critical:");
            break;
        case QtFatalMsg:
            logType = QString("Fatal:");
            isAbort=true;
            break;
    }

    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString contextInfo = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString message = QString("%1\t%2\t\t%3\t\t%4").arg(currentDateTime).arg(logType).arg(msg).arg(contextInfo);

    QFile file(applicationPath + QDir::separator() + "zLog." + QDateTime::currentDateTime().toString("yyyyMMdd") + ".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();

    if(isAbort)
    {
        abort();
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qInstallMessageHandler(myMessageOutput);
    applicationPath=QCoreApplication::applicationDirPath();
    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    QDir dir(applicationPath);
    dir.cdUp();
    viewer.loadFile(dir.absolutePath() + QDir::separator() + "html/index.html");
    return app.exec();
}
