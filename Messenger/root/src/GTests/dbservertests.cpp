#include "stdafx.h"

#include "gtest/gtest.h"

#include "user.h"
#include "dbpresenter.h"
#include "dbserverpresenter.h"

namespace DBServerTests
{
    DB::DBServerPresenter s_db("ServerTest1.db");

    TEST(DBServer, insertUser1)
    {
        EXPECT_TRUE(s_db.insertUser(User("user", "123", true)));
    }

    TEST(DBServer, insertUser2)
    {
        EXPECT_FALSE(s_db.insertUser(User("user", "123", true)));
    }

/*
    TEST(DBServer, getListOfClients)
    {
        QVector<User> vec;
        vec.push_back(User(1, "user", true));
        EXPECT_EQ(vec, s_db.getListOfUser());
    }
*/
    TEST(DBServer, searchStatus)
    {
        EXPECT_EQ(true, s_db.searchStatus(1));
    }

    TEST(DBServer, updateStatus)
    {
        EXPECT_TRUE(s_db.updateStatus(1,1));
    }

    TEST(DBServer, deleteDB )
    {
        EXPECT_NO_THROW(s_db.deleteDB());
    }

}
