#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include "shell.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * ==========
 * from inheritance
 * ==========
protected:
	bool truthVal;
	bool exitFlag;
	string origStr;

public:
	virtual void execute() = 0;
	virtual string getOrigStr() = 0
    virtual string getFormalStr() = 0;
    virtual void setBoolVals() = 0;

	bool isFalse() {
	    return this->truthVal;
	}
	bool isExit () {
	    return this->exitFlag;
	}
 * =========
 * end inheritance
 * =========
 */

class Command: public Shell {

protected:
    vector<string> words;

public:
    Command(){}

    virtual void execute() = 0;
    virtual void setBoolVals() = 0;
    virtual string getOrigStr() {
        return this->origStr;
    }

    virtual string getFormalStr() {
        string res = "";
        for (int i = 0; i < this->words.size() - 1; i++) {
            res = res + this->words.at(i) + " ";
        }
        res += this->words.at(this->words.size() - 1);
        return res;
    }

};

#endif