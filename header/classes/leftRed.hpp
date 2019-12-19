#ifndef __LEFTRED_HPP__
#define __LEFTRED_HPP__

#include <iostream>
#include "redirect.hpp"

using namespace std;

class LeftRed: public Redirect {

//protected:
//    bool falseFlag;
//    bool exitFlag;
//    string origStr;

public:
    LeftRed(string str){
        this->origStr = str;
        this->setBoolVals();
    }

    virtual void execute() {
        if (!this->falseFlag) {
            string command = this->origStr.substr(0, lessPos(this->origStr));
            string filename = removeSpacesFrontNBack(this->origStr.substr(lessPos(this->origStr) + 1));

    //        cout << "COMMAND: " << command << endl;
    //        cout << "FILE: " << filename << endl;

            char *output = new char[filename.length() + 1];
            strcpy(output, filename.c_str());

            vector<string> v = parseSpace(command);
            char *args[v.size() + 1];
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
                int ofd = open(output, 0644);

                dup2(ofd, STDIN_FILENO);
                execvp(args[0], args);
            }
            while (wait(NULL) != pid) {}
        } else {
            cout << "file not found" << endl;
        }
    };
    virtual void setBoolVals() {
        string filename = removeSpacesFrontNBack(this->origStr.substr(lessPos(this->origStr) + 1));
        char *output = new char[filename.length() + 1];
        strcpy(output, filename.c_str());

        struct stat buf;
        const char *str = output;
        stat(str, &buf);
        int fStat = S_ISREG(buf.st_mode);
        this->falseFlag = !(fStat != 0);

        this->exitFlag = false;
    };


};

#endif
