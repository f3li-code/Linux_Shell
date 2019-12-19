#ifndef __PARSEPIPE_HPP__
#define __PARSEPIPE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include "redirection.hpp"
using namespace std;

vector<string> parsePipe(string str) {
    vector<string> res;
    if (!hasOnePipe(str)) {
        res.push_back(str);
        return res;
    }

    int start = 0, end = 0;
    while (onePipePos(str, start) != -1) {
        end = onePipePos(str, start);
        res.push_back(str.substr(start, (end - start)));
        start = end + 2;
    }
    res.push_back(str.substr(start, (str.length() - start)));

    return res;
}

#endif
