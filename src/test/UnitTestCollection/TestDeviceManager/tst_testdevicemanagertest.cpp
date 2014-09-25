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
            deviceManager->GetSensors();
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
