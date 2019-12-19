#ifndef __OPERATOR_HPP__
#define __OPERATOR_HPP__

#include <iostream>
#include <string>

#include "shell.hpp"
 
using namespace std;

/*
 * ==========
 * from shell
 * ==========
protected:
	bool falseFlag;
	bool exitFlag;
	string origStr;

public:
	virtual void execute() = 0;
	virtual string getOrigStr() = 0;
    virtual string getFormalStr() = 0;
    virtual void setBoolVals() = 0;

	bool isFalse() {
	    return this->falseFlag;
	}
	bool isExit () {
	    return this->exitFlag;
	}
 * =========
 * end shell
 * =========
 */

class Shell;

class Operator : public Shell {
    
protected:
	Shell* leftCommand;
	Shell* rightCommand;

public:
	Operator(){}

	virtual void execute() = 0;
	virtual string getOrigStr() = 0;
	virtual string getFormalStr() = 0;
};

#endif
