#include <QString>
#include <QtTest>
#include "../../../app/algorithms/IAlgorithm/ialgorithm.h"
#include "../../../app/algorithms/SimpleAlgorithm/simplealgorithm.h"


class TestSimpleSectionAlgorithmTest : public QObject
{
    Q_OBJECT

public:
    TestSimpleSectionAlgorithmTest();


private Q_SLOTS:
    void PassTestExecuteOperation();
};

TestSimpleSectionAlgorithmTest::TestSimpleSectionAlgorithmTest()
{
}

void TestSimpleSectionAlgorithmTest::PassTestExecuteOperation()
{
    IAlgorithm *algorithm=new SimpleAlgorithm;
    QVERIFY(algorithm!=NULL);
    algorithm->dataStore.insert("sensortype","temprature");
    algorithm->dataStore.insert("name","Tomato");
    algorithm->dataStore.insert("id","1");
    algorithm->PreSetup();
    QVERIFY(algorithm->ExecuteOperation("100")==true);
}

QTEST_MAIN(TestSimpleSectionAlgorithmTest)

#include "tst_testsimplesectionalgorithmtest.moc"
