#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
/*#include "../../../app/algorithms/IAlgorithm/ialgorithm.h"
#include "../../../app/algorithms/SimpleAlgorithm/simplealgorithm.h"
#include "../../../app/sharelibs/CommonVariables/commonvariables.h"
#include "../../../app/device/SensorBase/sensorbase.h"
#include "../../../app/device/DeviceBase/devicebase.h"
#include "../../../app/device/Sensors/sensor.h"
#include "../../../app/device/ControlHardwareManager/controlhardwaremanager.h"*/

#include "../../../app/device/Hardware/hardware.h"

class TestSensorsTest : public QObject
{
    Q_OBJECT

public:
    TestSensorsTest();

signals:

    void TestForHardwareReceieverSlot(QString bundlData);

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void TestSensorInitialization();
};

TestSensorsTest::TestSensorsTest()
{
}

void TestSensorsTest::initTestCase()
{
}

void TestSensorsTest::cleanupTestCase()
{
}

bool LoadPlugin()
{
    QDir pluginsDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");

    pluginsDir.cd("debug");


    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        qDebug() << "File Name=" + fileName;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            IHardware* echoInterface = qobject_cast<IHardware *>(plugin);
            if (echoInterface)
            {//sensortype
                QMap<QString, QVariant> data;
                QVariant id(QString("01"));
                QVariant sensorType(QString("Temprature"));
                data.insert("id", id);
                data.insert("sensortype", sensorType);

                echoInterface->SetHardware(data);
                qDebug()<<echoInterface->GetDeviceID();
                return true;
            }
        }
    }

    return false;
}

void TestSensorsTest::TestSensorInitialization()
{
    QDir pluginsDir(qApp->applicationDirPath());

    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
    #endif
        pluginsDir.cd("plugins");

    pluginsDir.cd("debug");


    QString file="SensorUnit.dll";
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(file));
    QObject *plugin = pluginLoader.instance();

    if (plugin) {

        IHardware* sensor = qobject_cast<IHardware *>(plugin);

        if (sensor)
        {
            QMap<QString, QVariant> data;
            QVariant id(QString("01"));
            QVariant sensorType(QString("Temprature"));

            data.insert("id", id);
            data.insert("sensortype", sensorType);
            sensor->SetHardware(data);

            qDebug()<<sensor->GetDeviceType();
        }
    }

    /*SensorBase *sensor=new Sensor("01",CommonVariables::Temprature);
    IAlgorithm *algorithm=new SimpleAlgorithm;
    ControlHardwareManager controlMananger;
    connect(this, SIGNAL(TestForHardwareReceieverSlot(QString)), &controlMananger, SLOT(HardwareReceieverSlot(QString)));
    connect(sensor, SIGNAL(FreeSignal(QVariant)), algorithm, SLOT(OperateDataReceiever(QVariant)));
    connect(algorithm, SIGNAL(EmitDeviceControlCode(QList<QString>)), &controlMananger, SLOT(CommandSlotC(QList<QString>)));

    sensor->BuildHardwareInputConnection(&controlMananger);
    sensor->SetAlgorithm(algorithm);
    QVariant freeData="1" ;
    emit sensor->FreeSignal(freeData);

    QString data="Q01CP35AA*";
    int timepassby=0;
    int sleepSeconds=1;

    while(timepassby!=60)
    {
        qDebug()<<"-----------------[" + QString::number(timepassby,10) +  "]-----------------";

        if(timepassby == 12)
        {
            data="Q01CP199AA*";
        }
        else if(timepassby == 23)
        {
            data="Q01CN199AA*";
        }

        emit this->TestForHardwareReceieverSlot(data);

        timepassby++;
        QThread::sleep(sleepSeconds);
    }

    QVERIFY2(true, "Failure");*/
}

QTEST_MAIN(TestSensorsTest)

#include "tst_testsensorstest.moc"
