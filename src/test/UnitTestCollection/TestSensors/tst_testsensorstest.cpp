#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../app/algorithms/IAlgorithm/ialgorithm.h"
#include "../../../app/algorithms/SimpleAlgorithm/simplealgorithm.h"
#include "../../../app/sharelibs/CommonVariables/commonvariables.h"
#include "../../../app/device/SensorBase/sensorbase.h"
#include "../../../app/device/DeviceBase/devicebase.h"
#include "../../../app/device/Sensors/sensortemprature.h"

class TestSensorsTest : public QObject
{
    Q_OBJECT

public:
    TestSensorsTest();

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
    SensorBase *sensorTemprature=new SensorTemprature("01",SensorBase::Tempratue);

    QVERIFY2(true, "Failure");
}

QTEST_MAIN(TestSensorsTest)

#include "tst_testsensorstest.moc"
