#include <QString>
#include <QtTest>
#include <QDateTime>
#include "../../../app/algorithms/IAlgorithm/ialgorithm.h"
#include "../../../app/algorithms/SimpleAlgorithm/simplealgorithm.h"
#include <QThread>

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
    QString value="100";
    QVERIFY(algorithm!=NULL);
    algorithm->dataStore.insert("Temprature", value);
    algorithm->dataStore.insert("id","1");
    QVERIFY(algorithm->ExecuteOperation()==true);

    int timepassby=0;

    while(timepassby!=60)
    {
        qDebug()<<"-----------------[" + QString::number(timepassby,10) +  "]-----------------";

        if(timepassby == 12)
        {
            value="33";
        }
        else if(timepassby == 23)
        {
            value="-6";
        }

        algorithm->dataStore.insert("Temprature", value);
        algorithm->dataStore.insert("id","1");
        QVERIFY(algorithm->ExecuteOperation()==true);
        timepassby++;
        QThread::sleep(1);
    }

    /*QString format = "ddd,dd MMM yyyy HH:mm:ss";
    QLocale loc = QLocale(QLocale::English, QLocale::UnitedStates);
    QDateTime t = QDateTime::currentDateTime();
    qDebug() << loc.toString( t, format);*/

}

QTEST_MAIN(TestSimpleSectionAlgorithmTest)

#include "tst_testsimplesectionalgorithmtest.moc"
