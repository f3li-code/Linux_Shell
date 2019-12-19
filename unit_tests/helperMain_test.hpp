#ifndef __HELPER_MAIN_TEST_HPP__
#define __HELPER_MAIN_TEST_HPP__

#include "../header/helper/helperMain.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

TEST(removePound, test1){
	string input_string = "#hello there";
	string result_string = removePound(input_string);
	EXPECT_EQ(result_string,"");
}

TEST(removePound, test2){
        string input_string = "hello #there";
        string result_string = removePound(input_string);
        EXPECT_EQ(result_string,"hello ");
}

TEST(removePound, test3){
        string input_string = "hello there";
        string result_string = removePound(input_string);
        EXPECT_EQ(result_string,"hello there");
}

TEST(removePound, test4){
        string input_string = "hello there#";
        string result_string = removePound(input_string);
        EXPECT_EQ(result_string,"hello there");
}


TEST(quotesValidity, t1) {
    string in0 = "";
    string in1 = "\"";
    string in2 = "\"\"";
    string in3 = "\"\"\"";
    string in4 = "\"\"\"\"";
    string in1P = "\"#\"";
    EXPECT_EQ(hasValidQuotes(in0), true);
    EXPECT_EQ(hasValidQuotes(in1), false);
    EXPECT_EQ(hasValidQuotes(in2), true);
    EXPECT_EQ(hasValidQuotes(in3), false);
    EXPECT_EQ(hasValidQuotes(in4), true);
    EXPECT_EQ(hasValidQuotes(in1P), true);
}

#endif 
