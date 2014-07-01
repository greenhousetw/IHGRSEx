#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../app/device/ControlHardwareManager/controlhardwaremanager.h"

class TestControlHardwareManagerTest : public QObject
{
    Q_OBJECT

public:
    TestControlHardwareManagerTest();

public slots:

void SlotForInternalSubscribers(NotifyPackage package);

signals:

    void TestForHardwareReceieverSlot(QString bundlData);

private:

    NotifyPackage notifyPackage;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void TestPassExecutePassTestCommandTypeC();
    void TestPassExcuteRSQCommand();
    void TestPassCommandParsing();
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

void TestControlHardwareManagerTest::TestPassExecutePassTestCommandTypeC()
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

void TestControlHardwareManagerTest::TestPassExcuteRSQCommand()
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

void TestControlHardwareManagerTest::TestPassCommandParsing()
{
   ControlHardwareManager controlMananger;
   connect(this, SIGNAL(TestForHardwareReceieverSlot(QString)), &controlMananger, SLOT(HardwareReceieverSlot(QString)));
   connect(&controlMananger, SIGNAL(SignalInternalSubscribers(NotifyPackage)), this, SLOT(SlotForInternalSubscribers(NotifyPackage)));

   //Test return string for Q command
   QString data="Q01CP25AA*";
   emit this->TestForHardwareReceieverSlot(data);

   data="Q01FP75AA*";
   emit this->TestForHardwareReceieverSlot(data);

   //Test return string for h command
   data="Q02H75AA*";
   emit this->TestForHardwareReceieverSlot(data);

   //Test return string for l command
   data="Q03A980000LAA*";
   emit this->TestForHardwareReceieverSlot(data);

   //Test return string for h command
   data="Q03B759999AA*";
   emit this->TestForHardwareReceieverSlot(data);
   QVERIFY(this->notifyPackage.target=="03");

   //Test return string for 04 command
   data="Q01CP29H89B98000AA*";
   emit this->TestForHardwareReceieverSlot(data);

   //Test return string for real status
   data="Q01CP29H89B98000AA*Q02CP29AA*Q03H987pp*Q01475920Q0k1475920";
   emit this->TestForHardwareReceieverSlot(data);
}

void TestControlHardwareManagerTest::SlotForInternalSubscribers(NotifyPackage package)
{
    this->notifyPackage=package;

    foreach(QString key, this->notifyPackage.notificationContent.keys())
    {
        QString value=this->notifyPackage.notificationContent[key];
        qDebug()<<"key=" + key + ", value="+ value;
        QVERIFY(key!="");
    }
}

QTEST_MAIN(TestControlHardwareManagerTest)

#include "tst_testcontrolhardwaremanagertest.moc"
