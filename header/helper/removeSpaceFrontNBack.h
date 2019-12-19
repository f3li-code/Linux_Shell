//
// Created by Fangzhong Li on 12/12/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_REMOVESPACEFRONTNBACK_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_REMOVESPACEFRONTNBACK_H

#include <string>
#include <iostream>
using namespace std;

string removeSpacesFrontNBack (string str) {
    string tmp = str;
    int i = 0;
    while (tmp[i] == ' ') {
        i++;
    }
    tmp = tmp.substr(i, (tmp.length() - i));

    i = tmp.length() - 1;

    while (tmp[i] == ' ') {
        i--;
    }
    tmp = tmp.substr(0, (i + 1));
    return tmp;

}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_REMOVESPACEFRONTNBACK_H
