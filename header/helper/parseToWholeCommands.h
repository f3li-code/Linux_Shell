//
// Created by Fangzhong Li on 11/26/19.
//

// Wed Done
#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_PARSETOWHOLECOMMANDS_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_PARSETOWHOLECOMMANDS_H

#include <vector>
#include <stack>
#include <iostream>

using namespace std;

vector<string> parseToWholeCommands(string in) {
    vector<string> res;
    // out << "parse to whole commands" << endl;

    if (in[in.length() - 1] != ';') in += ';';
    bool openQuotes = false;
    stack<char> parenSt;

    int start = 0;

    for (int i = 0; i < in.length(); i++) {
        if (in[i] == '"') openQuotes = !openQuotes;
        if (!openQuotes) {
            if (in[i] == '(') parenSt.push('(');
            if (in[i] == ')') parenSt.pop();
        }
        if (!openQuotes && parenSt.empty()) {
            if (in[i] == ';') {
                res.push_back(in.substr(start, (i - start)));
                start = i + 1;
            }
        }
    }
//    for (int i = 0; i < res.size(); i++) {
//        cout << res.at(i) << endl;
//    }
    return res;
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_PARSETOWHOLECOMMANDS_H
