#ifndef __RIGHTRED_HPP__
#define __RIGHTRED_HPP__

#include <iostream>
#include "redirect.hpp"

using namespace std;

class RightRed: public Redirect {

//protected:
//    bool falseFlag;
//    bool exitFlag;
//    string origStr;

public:
    RightRed(string str){
        this->origStr = str;
        this->setBoolVals();
    }

    virtual void execute() {
        string command = this->origStr.substr(0, oneGreaterPos(this->origStr));
        string filename = removeSpacesFrontNBack(this->origStr.substr(oneGreaterPos(this->origStr) + 1));

        char* output = new char[filename.length() + 1];
        strcpy(output, filename.c_str());

        vector<string> v = parseSpace(command);
        char* args [v.size() + 1];
        for (int i = 0; i < v.size(); i++) {
            args[i] = new char[v.at(i).length() + 1];
            strcpy(args[i], v.at(i).c_str());
        }
        args[v.size()] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
        }
        if (pid == 0) {
            int ofd = creat(output, 0644);
            dup2(ofd, STDOUT_FILENO);
            execvp(args[0], args);
        }
        while (wait(NULL) != pid){}
    };
    virtual void setBoolVals() {
        this->falseFlag = false;
        this->exitFlag = false;
    };


};

#endif
