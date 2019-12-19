//
// Created by Fangzhong Li on 11/26/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_PARSETOWHOLECOMMAND_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_PARSETOWHOLECOMMAND_TEST_H

#include "../header/helper/parseToWholeCommands.h"
#include <iostream>

using namespace std;

TEST(parseWholeCommand, t1) {
    string input = "(\"echo\" abc; ls) && ls -a";
    vector<string> sup; sup.push_back("(\"echo\" abc; ls) && ls -a");
    EXPECT_EQ(parseToWholeCommands(input), sup);
}

TEST(parseWholeCommand, t2) {
    string input = "()\";\"; abc";
    vector<string> sup; sup.push_back("()\";\""); sup.push_back(" abc");
    EXPECT_EQ(parseToWholeCommands(input), sup);
}

TEST(parseWholeCommand, t3) {
    string input = "(;);abc";
    vector<string> sup(2, ""); sup.at(0) = "(;)"; sup.at(1) = "abc";
    EXPECT_EQ(parseToWholeCommands(input), sup);
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_PARSETOWHOLECOMMAND_TEST_H
