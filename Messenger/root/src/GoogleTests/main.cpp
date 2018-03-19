#include "tst_dbtestscreate.h"

#include "gtest/gtest.h"

/*
TEST(DBTestsCreate, DBTests)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
