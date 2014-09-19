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
#include "../../../app/device/Tranceiver/tranceiver.h"
#include "../../../app/device/TrancieverLoader/trancieverloader.h"
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
    void TestSensorRight();
    //void TestSensorCreation();
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

void TestSensorsTest::TestSensorRight()
{
    IDeviceFactory* factory=NULL;
    IDeviceFactory* tranceiverfactory=NULL;

    QPluginLoader loader;

    QPluginLoader tranceiverLoader;

    CoreOne core;

    if (PluginHelper::GetPlugIn(loader, "SensorPlugInLoader.dll") &&
        PluginHelper::GetPlugIn(tranceiverLoader, "TrancieverLoader.dll")
            ) {

        factory = qobject_cast<IDeviceFactory *>(loader.instance());

        tranceiverfactory = qobject_cast<IDeviceFactory *>(tranceiverLoader.instance());

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

        info.clear();
        info.insert("id", QVariant(QString("01")));
        info.insert("TranceiverType", QVariant(QString("SerialPort")));
        Tranceiver* tranceiver = (Tranceiver*) tranceiverfactory->GetDevice(info);
        tranceiver->SetHardware(info);
        tranceiver->CoreConnector(core);

        foreach(Sensor* sensor, sensorList)
        {
            DataPacket datapacket;
            datapacket.packetData.value="12";
            emit sensor->SendData(datapacket);

            if(sensor->DiconnectCoreConnector(core))
            {
               qDebug()<<"Core detached";
               delete sensor;
            }
        }
    }

    loader.unload();

    QVERIFY2(true, "Failure");
}

QTEST_MAIN(TestSensorsTest)

#include "tst_testsensorstest.moc"
