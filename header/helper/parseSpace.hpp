#ifndef __HELPER_OP_HPP__
#define __HELPER_OP_HPP__

#include <string>
#include <iostream>

using namespace std;

vector<string> parseSpace (string str) {
    // remove possible spaces in front of the string
    int l = str.length();
    int i = 0;
    string tmp = str;
    while (tmp[i] == ' ') {
	i++;
    }
    tmp = tmp.substr(i, (l - i));

    // remove possible spaces behind the string
    l = tmp.length();
    i = l - 1;
    while (tmp[i] == ' ') {
	i--;
    }	
    tmp = tmp.substr(0, (i + 1));
    // cout << "test: " << endl;
    // cout << "|" << tmp << "|" << endl;

    l = tmp.length();
    vector<string> res;
    int start = 0;
    for (i = 0; i < l; i++) {
	if (tmp[i] == ' ') {
	    res.push_back(tmp.substr(start, (i - start)));
	    while (i < l && tmp[i] == ' ') {
		i++;
	    }
	start = i;
	}
    }
    // push the last word into the vector
    res.push_back(tmp.substr(start, (l - start))); 

    return res;
}

#endif
