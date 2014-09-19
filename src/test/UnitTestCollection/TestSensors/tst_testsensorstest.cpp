#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include <QList>

#include "../../../app/core/Core/core.h"
#include "../../../app/core/Core/coreone.h"
#include "../../../app/device/Hardware/hardware.h"
#include "../../../app/device/IDeviceFactory/idevicefactory.h"
#include "../../../app/device/SensorUnit/sensor.h"
#include "../../../app/device/SensorPlugInLoader/sensorpluginloader.h"
#include "../../../app/sharelibs/PluginHelper/pluginhelper.h"

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
    void TestSensorCoreConnection();
    void TestSensorCreation();
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

void TestSensorsTest::TestSensorCoreConnection()
{
    IDeviceFactory* factory=NULL;

    QPluginLoader loader;

    CoreOne core;

    if (PluginHelper::GetPlugIn(loader, "SensorPlugInLoader.dll")) {

        factory = qobject_cast<IDeviceFactory *>(loader.instance());

        QMap<QString, QVariant> info;

        QString dataMetrix[3][2]={{"01","Temprature"},{"02","Humid"},{"03","Light"}};

        QList<Sensor*> sensorList;

        for(int i=0;i<3;i++)
        {
            info.insert("id", QVariant(QString(dataMetrix[i][0])));
            info.insert("sensortype", QVariant(QString(dataMetrix[i][1])));
            Sensor* sensor = (Sensor*) factory->GetDevice(info);
            sensor->SetHardware(info);
            sensor->CoreConnector(core);
            sensorList.push_back(sensor);
            info.clear();
        }

        QVERIFY(sensorList.at(1)->GetDeviceType()=="Humid");
    }

    loader.unload();
}

void TestSensorsTest::TestSensorCreation()
{
    IDeviceFactory* factory=NULL;

    QPluginLoader loader;

    if (PluginHelper::GetPlugIn(loader, "SensorPlugInLoader.dll")) {

        factory = qobject_cast<IDeviceFactory *>(loader.instance());

        QMap<QString, QVariant> info;

        QString dataMetrix[3][2]={{"01","Temprature"},{"02","Humid"},{"03","Light"}};

        QList<Sensor*> sensorList;

        for(int i=0;i<3;i++)
        {
            info.insert("id", QVariant(QString(dataMetrix[i][0])));
            info.insert("sensortype", QVariant(QString(dataMetrix[i][1])));
            Sensor* sensor = (Sensor*) factory->GetDevice(info);
            sensor->SetHardware(info);
            sensorList.push_back(sensor);
            info.clear();
        }

        QVERIFY(sensorList.at(1)->GetDeviceType()=="Humid");
    }

    loader.unload();

    QVERIFY2(true, "Failure");
}


QTEST_MAIN(TestSensorsTest)

#include "tst_testsensorstest.moc"
