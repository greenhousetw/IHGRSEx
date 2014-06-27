#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../app/device/ControlHardwareManager/controlhardwaremanager.h"

class TestControlHardwareManagerTest : public QObject
{
    Q_OBJECT

public:
    TestControlHardwareManagerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void ExecutePassTestCommandTypeC();
    void ExcuteRSQCommand();
};

TestControlHardwareManagerTest::TestControlHardwareManagerTest()
{
}

void TestControlHardwareManagerTest::initTestCase()
{    
}

void TestControlHardwareManagerTest::cleanupTestCase()
{
}

void TestControlHardwareManagerTest::ExecutePassTestCommandTypeC()
{
    ControlHardwareManager hardwareManager;
    QList<QString> machinestatus;
    machinestatus.append("coolingfan.off");
    machinestatus.append("exhaustfanlv4.on");
    machinestatus.append("lightingno1no3.on");
    machinestatus.append("mixer.off");
    hardwareManager.CommandSlotC(machinestatus);
    QVERIFY2(true, "Failure");
}

void TestControlHardwareManagerTest::ExcuteRSQCommand()
{
    ControlHardwareManager hardwareManager;
    QHash<QString, QString> data;
    QString nodeid="";
    data.insert("room.temprature",nodeid);
    data.insert("room.all",nodeid);
    data.insert("room.C",nodeid);
    hardwareManager.commandType=ControlHardwareManager::gethardwareQtype;
    hardwareManager.CommandSlotRSQ(data);
    data.clear();
    data.insert("config",nodeid);
    hardwareManager.commandType=ControlHardwareManager::gethardwareRtype;
    hardwareManager.CommandSlotRSQ(data);
    data.clear();
    data.insert("setF",nodeid);
    data.insert("LutronA",nodeid);
    data.insert("LutronC",nodeid);
    hardwareManager.commandType=ControlHardwareManager::gethardwareStype;
    hardwareManager.CommandSlotRSQ(data);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(TestControlHardwareManagerTest)

#include "tst_testcontrolhardwaremanagertest.moc"
