#ifndef __PIPE2_HPP__
#define __PIPE2_HPP__

#include <iostream>
#include "redirect.hpp"
#include "execCommand.hpp"

using namespace std;

class Pipe2: public Redirect {

//protected:
//    bool falseFlag;
//    bool exitFlag;
//    string origStr;
private:
    string first_str;
    string second_str;
    bool isList;

public:
    Pipe2(string str){
        this->origStr = str;
        this->setBoolVals();
    }

    virtual void execute() {
        if (!this->falseFlag) {
            if (this->isList) {
                Shell* ls = new ExecCommand(removeSpacesFrontNBack(this->origStr.substr(onePipePos(this->origStr) + 1)));
                ls->execute();
                return;
            } else {
                this->exec_all();
                return;
            }
        }
        return;
    }

    virtual void setBoolVals() {
        int pos = onePipePos(this->origStr);

        string c1_str = this->origStr.substr(0, pos);
        string c2_str = this->origStr.substr(pos + 1);

        this->isList = (removeSpacesFrontNBack(c2_str).substr(0, 2) == "ls");
        this->falseFlag = (removeSpacesFrontNBack(c2_str) == "false");
        this->exitFlag = false;

        this->first_str = c1_str;
        this->second_str = c2_str;

        if (removeSpacesFrontNBack(this->first_str) == "exit") this->first_str = "false";
        if (removeSpacesFrontNBack(this->second_str) == "exit") this->second_str = "false";
        return;
    }

private:
    void exec_all(){
        //int pos = onePipePos(this->origStr);
        // command 1 args prep
        // tring c1_str = this->origStr.substr(0, pos);
        vector<string> c1_v = parseSpace(this->first_str);
        char* c1_args[c1_v.size()+1];

        // cout << "main c1_args:" << endl;
        for (int i = 0; i < c1_v.size(); i++) {
            c1_args[i] = new char[c1_v.at(i).length() + 1];
            strcpy(c1_args[i], c1_v.at(i).c_str());
            // cout << c1_args[i] << endl;
        }
        c1_args[c1_v.size()] = NULL;

        // c2 args below:
        // string c2_str = this->origStr.substr(pos + 1);
        vector<string> c2_v = parseSpace(this->second_str);

        char* c2_args[c2_v.size()+2];   // leave a space for filename

        // cout << "main c2_args:" << endl;
        for (int i = 0; i < c2_v.size(); i++) {
            c2_args[i] = new char[c2_v.at(i).length() + 1];
            strcpy(c2_args[i], c2_v.at(i).c_str());
            // cout << c2_args[i] << endl;
        }
        c2_args[c2_v.size() + 1] = NULL;

//=====================================

        int pipefd[2], status;
        pid_t pid;

        char file[] = " ";
        char* outFile = file;
        c2_args[c2_v.size()] = outFile;
        int tmpfd = 0;
        // pipe(pipefd);

        pid = fork();
        if (pid < 0) {
            perror("fork()");
        }
        if (pid == 0) {
            // close(pipefd[READ]);
            tmpfd = creat(outFile, 0644);
            dup2(tmpfd, STDOUT_FILENO);
            if (execvp(c1_args[0], c1_args) == -1) {
                perror("execvp");
            }
        }

        while (wait(NULL) != pid){}
        pid = fork();
        if (pid < 0) {
            perror("fork2()");
        }
        if (pid == 0) {
            if (execvp(c2_args[0], c2_args) == -1) {
                perror("execvp()");
            }
        }

//    close(pipefd[READ]);
//    close(pipefd[WRITE]);

        // waitpid(-1, &status, 0);
        waitpid(-1, &status, 0);
    }

};

#endif