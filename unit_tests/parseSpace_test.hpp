#ifndef __PARSESPACE_TEST_HPP
#define __PARSESPACE_TEST_HPP

#include "../../header/helper/parseSpace.hpp"
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST(parseSpace, test1) {
    string i = "  ls  ls ls  ";
    vector<string> supposedly;
    supposedly.push_back("ls"); 
    supposedly.push_back("ls");
    supposedly.push_back("ls");
    vector<string> actual = parseSpace (i);
    EXPECT_EQ(supposedly, actual);
}

TEST(parseSpace, noSpace) {
    string i = "ahahahahahaha";
    vector<string> supposedly;
    supposedly.push_back("ahahahahahaha");
    EXPECT_EQ(parseSpace(i), supposedly);
}

TEST(parseSpace, allSpace) {
    string i = "    ";
    vector<string> supposedly;
    supposedly.push_back("");
    EXPECT_EQ(parseSpace(i), supposedly); 
}
#endif
