#include <QQueue>
#include <QTime>
#include <QVector>
#include <QtSql/QSqlDatabase>

#include "gtest/gtest.h"

#include "dbpresenter.h"
#include "dbclientpresenter.h"

namespace DBClientTests
{
    DB::DBClientPresenter s_db("ClientDBTest.db");

TEST(DBClientTests, createDB)
{
    EXPECT_NO_THROW(s_db.createConnection());
}


TEST(DBClientTests, insertDialog)
{
    if(s_db.searchIdDialog(1) == 0)
        EXPECT_TRUE(s_db.insertDialog(1));
    else
        EXPECT_FALSE(s_db.insertDialog(1));
}


TEST(DBClientTests, searchIDDialog)
{
    if(s_db.searchIdDialog(1) == 0)
        EXPECT_TRUE(s_db.insertDialog(1));
    else
        EXPECT_FALSE(s_db.insertDialog(1));
}

TEST(DBClientTests,insertMessage )
{
    EXPECT_TRUE(s_db.insertMessage(1, true, "Hello", QTime::currentTime().toString()));
}

TEST(DBClientTests,showDialog )
{
    QQueue<QString> q;
    EXPECT_EQ(q, s_db.showDialog(0));
}

TEST(DBClientTests, deleteDB )
{
    EXPECT_NO_THROW(s_db.deleteDB());
}

}
