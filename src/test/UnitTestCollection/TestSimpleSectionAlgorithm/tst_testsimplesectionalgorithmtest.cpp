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
    algorithm->dataStore.insert("Temprature", "100");
    algorithm->dataStore.insert("id","1");
    QVERIFY(algorithm->ExecuteOperation()==true);
}

QTEST_MAIN(TestSimpleSectionAlgorithmTest)

#include "tst_testsimplesectionalgorithmtest.moc"
