//
// Created by Fangzhong Li on 11/27/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_ASSEMBLEHELPER_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_ASSEMBLEHELPER_H

#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isParen(string str) {
    // cout << "isParen" << endl;
    if (str[0] != '(') return false;

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') c++;
        if (str[i] == ')') c--;
        if (c == 0 && i != str.length() - 1) {
            return false;
        }
    }

    return true;
}

string stripParen(string str) {
    return str.substr(1, str.length() - 2);
}

#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_ASSEMBLEHELPER_H
