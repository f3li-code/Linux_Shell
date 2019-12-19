#ifndef __REDIRECTION_TEST_HPP__
#define __REDIRECTION_TEST_HPP__

#include "../header/helper/redirection.hpp"

TEST(left, t1) {
    string a = "mac < and cheese";
    string b = "mac \" < \" and cheese";
    EXPECT_EQ(hasLess(a), true);
    EXPECT_EQ(hasLess(b), false);
}

TEST(oneright, t1) {
    string a = "mac > and cheese";
    string b = "mac \" > \" and cheese";
    EXPECT_EQ(hasOneGreater(a), true);
    EXPECT_EQ(hasOneGreater(b), false);
}

TEST(tworight, t1) {
    string a = "mac >> and cheese";
    string b = "mac \" >> \" and cheese";
    EXPECT_EQ(hasTwoGreater(a), true);
    EXPECT_EQ(hasTwoGreater(b), false);
}

TEST(onepipe, t1) {
    string a = "mac | and cheese";
    string b = "mac \" | \" and cheese";
    EXPECT_EQ(hasOnePipe(a), true);
    EXPECT_EQ(hasOnePipe(b), false);
}
#endif