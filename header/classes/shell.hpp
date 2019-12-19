#ifndef __SHELL_HPP__
#define __SHELL_HPP__

#include <iostream>
using namespace std;

class Shell {

protected:
	bool falseFlag;
	bool exitFlag;
	string origStr;

public:
	Shell(){}
	
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

};

#endif
