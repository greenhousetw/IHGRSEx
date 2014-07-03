#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../app/algorithms/IAlgorithm/ialgorithm.h"
#include "../../../app/algorithms/SimpleAlgorithm/simplealgorithm.h"
#include "../../../app/sharelibs/CommonVariables/commonvariables.h"
#include "../../../app/device/SensorBase/sensorbase.h"
#include "../../../app/device/DeviceBase/devicebase.h"
#include "../../../app/device/Sensors/sensor.h"
#include "../../../app/device/ControlHardwareManager/controlhardwaremanager.h"

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

void TestSensorsTest::TestSensorInitialization()
{
    SensorBase *sensor=new Sensor("01",CommonVariables::Temprature);
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

    QVERIFY2(true, "Failure");
}

QTEST_MAIN(TestSensorsTest)

#include "tst_testsensorstest.moc"
