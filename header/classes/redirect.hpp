#ifndef __REDIRECT_HPP__
#define __REDIRECT_HPP__

#include "shell.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <cstring>
#include "../helper/parseSpace.hpp"
#include "../helper/redirection.hpp"
#include "../helper/removeSpaceFrontNBack.h"
using namespace std;

class Redirect: public Shell {

//protected:
//    bool falseFlag;
//    bool exitFlag;
//    string origStr;

public:
    Redirect(){}

    virtual void execute() = 0;
    virtual string getOrigStr() {
        return this->origStr;
    }
    virtual string getFormalStr() {
        return this->origStr;
    }

    virtual void setBoolVals() = 0;

    bool isFalse() {
        return this->falseFlag;
    }
    bool isExit () {
        return this->exitFlag;
    }

};

#endif
