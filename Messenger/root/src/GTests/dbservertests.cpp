#include "gtest/gtest.h"

#include <QVector>

#include "DataLib/user.h"
#include "dbpresenter.h"
#include "dbserverpresenter.h"

namespace DBServerTests
{

    TEST(DBServer, insertUser)
    {
        DB::DBServerPresenter s_db("ServerDBTest.db");
        if(s_db.searchID("user") == 0)
            EXPECT_TRUE(s_db.insertUser(Data::User("user", "123", true)));
        else
            EXPECT_FALSE(s_db.insertUser(Data::User("user", "123", true)));
    }

    TEST(DBServer, searchUser)
    {
        DB::DBServerPresenter s_db("ServerDBTest.db");
        s_db.insertUser(Data::User("user1", "123", true));
        std::shared_ptr<Data::User> us1 (new Data::User("user1", "123" , true));
        std::shared_ptr<Data::User> us2 = s_db.searchUser("user1");
        EXPECT_EQ(us1->getPassword(), us2->getPassword());
    }

    TEST(DBServer, searchID)
    {
        DB::DBServerPresenter s_db("ServerDBTest.db");
        EXPECT_EQ(1, s_db.searchID("user"));
    }


    TEST(DBServer, searchStatus)
    {
        DB::DBServerPresenter s_db("ServerDBTest.db");
        EXPECT_EQ(true, s_db.searchStatus(1));
    }


    TEST(DBServer, updateStatus)
    {
        DB::DBServerPresenter s_db("ServerDBTest.db");
        EXPECT_EQ(true, s_db.updateStatus(1,false));
    }

    TEST(DBServer, updateAllStatus)
    {
        DB::DBServerPresenter s_db("ServerDBTest.db");
        s_db.updateStatusAllClients(true);
        EXPECT_TRUE(s_db.searchStatus(1));
    }

    TEST(DBServer, deleteDB )
    {
        DB::DBServerPresenter s_db("ServerDBTest.db");
        EXPECT_NO_THROW(s_db.deleteDB());
    }
}
