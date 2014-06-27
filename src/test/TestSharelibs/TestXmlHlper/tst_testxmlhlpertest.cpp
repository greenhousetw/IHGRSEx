#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../../../app/sharelibs/XmlHelper/xmlhelper.h"

class TestXmlHlperTest : public QObject
{
    Q_OBJECT

public:
    TestXmlHlperTest();

private Q_SLOTS:
    void testCase1();
};

TestXmlHlperTest::TestXmlHlperTest()
{
}

void TestXmlHlperTest::testCase1()
{
    QXmlQuery* xmlDoc=XmlHelper::LoadXMLDocument("./UnitTest.XmlData.xml");
    QVERIFY(xmlDoc!=NULL);

    QStringList data;
    XmlHelper::GetNodeValues(xmlDoc, "//Data/Right/Name/string()", &data);

    QString expectedData="IHGRS";
    QCOMPARE(data[0], expectedData);


    int expectedInteger=9708023;
    int now=0;
    XmlHelper::GetAttributeValueInType(xmlDoc, "//Data/Right/Student/@id/string()", &now);
    QCOMPARE(now, expectedInteger);

    double expectedDouble=99.8;
    double current=0;
    XmlHelper::GetAttributeValueInType(xmlDoc, "//Data/Right/Student/@score/string()", &current);
    QCOMPARE(current, expectedDouble);

    bool expectedBool=true;
    bool currentBool=false;
    XmlHelper::GetAttributeValueInType(xmlDoc, "//Data/Right/Student/@selected/string()", &currentBool);
    QCOMPARE(currentBool, expectedBool);

    QString joey="Joey";
    QString currentJoey="";
    QStringList list;
    XmlHelper::GetNodeValues(xmlDoc, "//Data/Right/Student[@selected=\"true\"]/string()", &list);
    QCOMPARE(list[0], joey);
}

QTEST_MAIN(TestXmlHlperTest)

#include "tst_testxmlhlpertest.moc"
