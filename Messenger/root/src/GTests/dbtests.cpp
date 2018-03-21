#include <QQueue>
#include <QTime>
#include <QtSql/QSqlDatabase>

#include "gtest/gtest.h"

#include "idbpresenter.h"
#include "dbclientpresenter.h"

namespace
{
    DB::DBClientPresenter db;
}


TEST(DBTests,createDB1)
{

    EXPECT_NO_THROW(db.createConnection());
}


TEST(DBTests, insertDialog1)
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    EXPECT_TRUE(db.insertDialog(1));
}

TEST(DBTests, insertDialog2)
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    EXPECT_FALSE(db.insertDialog(1));
}

TEST(DBTests, searchIDDialog1)
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    EXPECT_EQ(1, db.searchIdDialog(1));
}

TEST(DBTests, searchIDDialog2)
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    EXPECT_EQ(0, db.searchIdDialog(5));
}

TEST(DBTests,insertMessage )
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    EXPECT_TRUE(db.insertMessage(1,true,"Hello", QTime::currentTime().toString()));
}

TEST(DBTests,showDialog1 )
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    QQueue<QString> q;

    EXPECT_EQ(q, db.showDialog(0));
}

TEST(DBTests,showDialog2 )
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    QQueue<QString> q;
    q.push_back(QString::number(true) +' '+ "Hello" +' '+ QTime::currentTime().toString());

    EXPECT_EQ(q, db.showDialog(1));
}

TEST(DBTests, deleteDB )
{
    DB::DBClientPresenter db;
    db.createDB("Client.db");

    EXPECT_NO_THROW(db.deleteDB());
}
