#include <QString>
#include <QtTest>
#include <QCoreApplication>

class DBUnitTests : public QObject
{
    Q_OBJECT

public:
    DBUnitTests();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
};

DBUnitTests::DBUnitTests()
{
}

void DBUnitTests::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void DBUnitTests::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(DBUnitTests)

#include "tst_dbunittests.moc"
