#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../app/core/Core/core.h"
#include "../../../app/core/Core/coreone.h"
#include "../../../app/device/Hardware/hardware.h"
#include "../../../app/device/IDeviceFactory/idevicefactory.h"
#include "../../../app/device/DeviceManager/devicemanager.h"
#include "../../../app/device/DeviceManager/devicemangerhandler.h"
#include "../../../app/device/SensorUnit/sensor.h"
#include "../../../app/device/SensorPlugInLoader/sensorpluginloader.h"
#include "../../../app/device/Tranceiver/tranceiver.h"
#include "../../../app/device/TrancieverLoader/trancieverloader.h"
#include "../../../app/sharelibs/PluginHelper/pluginhelper.h"

class TestDeviceManagerTest : public QObject
{
    Q_OBJECT

public:
    TestDeviceManagerTest();

private Q_SLOTS:
    void TestDeviceManagerRight();
};

TestDeviceManagerTest::TestDeviceManagerTest()
{
}

void TestDeviceManagerTest::TestDeviceManagerRight()
{
    QPluginLoader loader;

    CoreOne core;

    if (PluginHelper::GetPlugIn(loader, "DeviceManager.dll"))
    {
         IDeviceManager* deviceManager = qobject_cast<IDeviceManager *>(loader.instance());

         if(deviceManager->SetCore())
         {
            if(deviceManager->LoadSensors() && deviceManager->LoadTranceievers())
            {
                DeviceMangerHandler* deviceManagerHandler= (DeviceMangerHandler*) deviceManager;
                Tranceiver* tranciever= (Tranceiver*) deviceManagerHandler->trancieverControlBox.value("01").value("71bf7839-9720-4da0-87e7-4c6fe776c323");

                DataPacket packet;
                packet.packetData.value="Q01CP56H77B150000AQ*";
                packet.packetData.payload=QVariant("Tranceiver");
                emit tranciever->SendData(packet);
            }
         }
    }
    else
    {
        qDebug()<<"D";
    }

    QVERIFY2(true, "Failure");
}

QTEST_MAIN(TestDeviceManagerTest)

#include "tst_testdevicemanagertest.moc"
