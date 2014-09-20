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
    void TestGreenSensorInitialization();
    void TestGreenSensorEmitData();
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

void TestSensorsTest::TestGreenSensorInitialization()
{
    IDeviceFactory* factory=NULL;

    QPluginLoader loader;

    CoreOne core;

    if (PluginHelper::GetPlugIn(loader, "SensorPlugInLoader.dll"))
    {

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

            QVERIFY(sensorList.at(i)->GetDeviceID()==QString(dataMetrix[i][0]));
            QVERIFY(sensorList.at(i)->GetDeviceType()==QString(dataMetrix[i][1]));
        }


        foreach(Sensor* sensor, sensorList)
        {

           if(sensor->DiconnectCoreConnector(core))
           {
               qDebug()<<"Core detached";
               delete sensor;
           }
        }
    }

    loader.unload();
}

void TestSensorsTest::TestGreenSensorEmitData()
{
        CoreOne core;

        QPluginLoader sensorLoader, tranceiverLoader;

        PluginHelper::GetPlugIn(sensorLoader, "SensorPlugInLoader.dll");
        PluginHelper::GetPlugIn(tranceiverLoader, "TrancieverLoader.dll");

        IDeviceFactory* sensorFactory=NULL;
        IDeviceFactory* tranceiverfactory=NULL;

        sensorFactory=(IDeviceFactory*) qobject_cast<IDeviceFactory *>(sensorLoader.instance());
        tranceiverfactory=(IDeviceFactory*) qobject_cast<IDeviceFactory *>(tranceiverLoader.instance());


        QMap<QString, QVariant> info;
        info.insert("id", QVariant(QString("01")));
        info.insert("TranceiverType", QVariant(QString("SerialPort")));

        Tranceiver* tranceiver = (Tranceiver*) tranceiverfactory->GetDevice(info);
        tranceiver->SetHardware(info);    
        tranceiver->CoreConnector(core);

        info.clear();
        info.insert("id", QVariant(QString("01")));
        info.insert("sensortype", QVariant(QString("Temprature")));

        Sensor* sensor = (Sensor*) sensorFactory->GetDevice(info);
        sensor->SetHardware(info);
        sensor->CoreConnector(core);

        DataPacket packet;
        packet.packetData.value=QString::number(12.225);

        packet.packetData.payload=QVariant("Sensor");
        emit sensor->SendData(packet);

        packet.packetData.value="Q01A3005";
        packet.packetData.payload=QVariant("Tranceiver");
        emit tranceiver->SendData(packet);

        sensor->DiconnectCoreConnector(core);
        tranceiver->DiconnectCoreConnector(core);

        delete sensor;
        delete tranceiver;
        sensorLoader.unload();
        tranceiverLoader.unload();
}

QTEST_MAIN(TestSensorsTest)

#include "tst_testsensorstest.moc"
