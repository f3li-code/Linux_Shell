//
// Created by Fangzhong Li on 11/27/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_IDENTIFYTESTCOMMAND_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_IDENTIFYTESTCOMMAND_H

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

bool isTest_str(string str) {
    return (str.find("test") == 0 || (str[0] == '[' && str[str.length() - 1] == ']'));
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_IDENTIFYTESTCOMMAND_H
