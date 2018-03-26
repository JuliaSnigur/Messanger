#include "gtest/gtest.h"

#include "request.h"

namespace Request
{

    TEST(Request, insertData)
    {
       QString str = "INSERT INTO table (123) VALUES (123);";
       EXPECT_EQ(str,Request::insertData("table", "123", "123"));
    }

    TEST(Request, searchData)
    {
        QString str = "SELECT 123 FROM table WHERE 123" ;
        EXPECT_EQ(str,Request::searchData("table", "123", "123"));
    }


    TEST(Request, searchAllData)
    {
        QString str = "SELECT 123 FROM table";
        EXPECT_EQ(str,Request::searchAllData("table", "123"));
    }


    TEST(Request, updateAllData)
    {
        QString str ="UPDATE  table SET 123;";
        EXPECT_EQ(str,Request::updateAllData("table", "123"));
    }


}
