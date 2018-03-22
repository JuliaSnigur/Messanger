#include "stdafx.h"

#include "gtest/gtest.h"

#include "dbpresenter.h"
#include "dbclientpresenter.h"

namespace DBTests
{
    DB::DBClientPresenter s_db;

TEST(DBTests,createDB1)
{

    EXPECT_NO_THROW(s_db.createConnection());
}


TEST(DBTests, insertDialog1)
{
    s_db.createDB("Client.db");
    EXPECT_TRUE(s_db.insertDialog(1));
}

TEST(DBTests, insertDialog2)
{
    s_db.createDB("Client.db");
    EXPECT_FALSE(s_db.insertDialog(1));
}

TEST(DBTests, searchIDDialog1)
{
    s_db.createDB("Client.db");
    EXPECT_EQ(1, s_db.searchIdDialog(1));
}

TEST(DBTests, searchIDDialog2)
{
    s_db.createDB("Client.db");
    EXPECT_EQ(0, s_db.searchIdDialog(5));
}

TEST(DBTests,insertMessage )
{
    s_db.createDB("Client.db");
    EXPECT_TRUE(s_db.insertMessage(1,true,"Hello", QTime::currentTime().toString()));
}

TEST(DBTests,showDialog1 )
{
    s_db.createDB("Client.db");
    QQueue<QString> q;
    EXPECT_EQ(q, s_db.showDialog(0));
}

TEST(DBTests,showDialog2 )
{
    s_db.createDB("Client.db");
    QQueue<QString> q;
    q.push_back(QString::number(true) +' '+ "Hello" +' '+ QTime::currentTime().toString());
    EXPECT_EQ(q, s_db.showDialog(1));
}

TEST(DBTests, deleteDB )
{
    s_db.createDB("Client.db");
    EXPECT_NO_THROW(s_db.deleteDB());
}

}
