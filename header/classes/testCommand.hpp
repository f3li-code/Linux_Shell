#ifndef __TESTCOMMAND_HPP__
#define __TESTCOMMAND_HPP__

#include "command.hpp"
#include "../helper/parseSpace.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
 * ==========
 * from inheritance
 * ==========
protected:
	bool falseFlag;
	bool exitFlag;
	string origStr;
    vector<string> words;      - FROM COMMAND

public:
	virtual void execute() = 0;
	virtual string getOrigStr() = 0
    virtual string getFormalStr() = 0;
    virtual void setBoolVals() = 0;

	bool isFalse() {
	    return this->falseFlag;
	}
	bool isExit () {
	    return this->exitFlag;
	}
 * =========
 * end inheritance
 * =========
 */

class TestCommand: public Command {
private:
    bool isValid;
public:
    TestCommand(string line) {
        this->origStr = line;
        this->words = parseSpace(this->origStr);
        this->isValid = true;
        if ((this->words.at(0).find('[') != string::npos && this->words.at(0) != "[")
            || (this->words.at(this->words.size() - 1).find(']') != string::npos && this->words.at(this->words.size() - 1) != "]")) {
            this->isValid = false;
        }
        this->setToTestForm();
        this->setBoolVals();
    }

    virtual void execute() {
        if (!this->isValid) {
            cout << "error: invalid test command" << endl;
        }
        if (!this->isFalse()) {
            cout  << "(True)" << endl;
        } else {
            cout << "(False)" << endl;
        }
        // cout << "placeholder for TestCommand::execute()" << endl;
        return;
    }

    virtual void setBoolVals() {
        // initial values
        if (origStr == "test") {
            this->falseFlag = true;
            this->exitFlag = false;
            return;
        }
        if (!this->isValid) {
            this->falseFlag = true;
            this->exitFlag = false;
            return;
        }
        this->exitFlag = false;
        if (this->words.size() == 1) {
            this->falseFlag = true;
        }
        // confirm
        struct stat buf;
        const char* str = words.at(2).c_str();
        // cout << "the file/direct you are looking for is: " << words.at(2) << endl;

        stat(str, &buf);
        int dStat = S_ISDIR(buf.st_mode);
        int fStat = S_ISREG(buf.st_mode);

        if (this->words.at(1) == "-e") {
            falseFlag = !(dStat != 0 || fStat != 0);
        } else if (this->words.at(1) == "-f") {
            falseFlag = !(fStat != 0);
        } else if (this->words.at(1) == "-d") {
            falseFlag = !(dStat != 0);
        } else {
            falseFlag = true;
            exitFlag = false;
        }

        return;
    }


    // own functions
    void setToTestForm() {
        // string is already parsed into vector<string> words;
        if (this->origStr.find('-') == string::npos) {
            auto it = this->words.begin();
            this->words.insert(it + 1, "-e");
        }
        return;
    }
};
// test command errors: 10 - 19

#endif