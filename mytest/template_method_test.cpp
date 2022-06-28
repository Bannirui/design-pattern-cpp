#include <gtest/gtest.h>
#include <iostream>

TEST(TemplateMethodTest, basicTest)
{
    std::cout << "hello test" << std::endl;
    EXPECT_STREQ("BCDEFGH", "BCDEFGH");
}