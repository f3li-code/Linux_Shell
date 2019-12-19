#ifndef __HELPER_MAIN_HPP__
#define __HELPER_MAIN_HPP__

// Wed Done
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;


/*This function finds the pound sign within a string and removes the pound sign 
 including all the following characters after*/

string removePound(string input){
    bool openSemi = false;
    string res = "";
    int mark = input.length();
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '"') openSemi = !openSemi;
        if (!openSemi) {
            if (input[i] == '#') {
                mark = i;
            }
        }
    }
    res = input.substr(0, mark);
    // cout << "res: " << res << endl;
    return res;
}

bool hasValidQuotes(string input) {
    int c = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '"') c++;
    }
    return (c % 2 == 0);
}
bool hasValidParen(string input) {
    if (input[0] == ')') return false;
    stack<char> st;
    bool openQuote = false;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '"') openQuote = !openQuote;
        if (!openQuote) {
            if (input[i] == '(') {
                st.push('(');
            }
            if (input[i] == ')') {
                st.pop();
            }
        }
    }
    return (st.size() == 0);
}

#endif
