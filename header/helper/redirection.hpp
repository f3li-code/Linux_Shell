#ifndef __REDIRECTION_HPP__
#define __REDIRECTION_HPP__

#include <iostream>
#include <string>

using namespace std;

bool hasSymbol(string str, string tar) {
    tar = " " + tar + " ";
    int l = tar.length();
    bool openQ = false;
    for (int i = 0; i < str.length()-1; i++) {
        if (str[i] == '"') openQ = !openQ;
        if (!openQ) {
            if (str[i+1] == tar[1]) {
                if (str.substr(i, l) == tar) {
                    return true;
                }
            }
        }
    }
    return false;
}
int symbolLoc(string str, string tar, int pos=0) {
    tar = " " + tar + " ";
    int l = tar.length();
    bool openQ = false;
    for (int i = pos; i < str.length()-1; i++) {
        if (str[i] == '"') openQ = !openQ;
        if (!openQ) {
            if (str[i+1] == tar[1]) {
                if (str.substr(i, l) == tar) {
                    return i + 1;
                }
            }
        }
    }
    return -1;
}
bool hasLess(string str) {
    return hasSymbol(str, "<");
}
bool hasOneGreater(string str) {
    return hasSymbol(str, ">");
}
bool hasTwoGreater(string str) {
    return hasSymbol(str, ">>");
}
bool hasOnePipe(string str) {
    return hasSymbol(str, "|");
}

int lessPos(string str, int pos=0) {
    return symbolLoc(str, "<", pos);
}

int oneGreaterPos(string str, int pos=0) {
    return symbolLoc(str, ">", pos);
}

int twoGreaterPos(string str, int pos=0) {
    return symbolLoc(str, ">>", pos);
}

int onePipePos(string str, int pos=0) {
    return symbolLoc(str, "|", pos);
}

//==================================================Thurs=======
bool isRedirectCom(string str) {
    return (hasLess(str) || hasOneGreater(str) || hasTwoGreater(str) || hasOnePipe(str));
}
//==================================================Thurs=======
#endif