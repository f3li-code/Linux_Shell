#ifndef __PIPE3_HPP__
#define __PIPE3_HPP__

#include <iostream>
#include "redirect.hpp"
#include "execCommand.hpp"
using namespace std;

class Pipe3: public Redirect {

//protected:
//    bool falseFlag;
//    bool exitFlag;
//    string origStr;
private:
    string first_str;
    bool second_isList;
    string second_str;
    bool third_isList;
    string third_str;

public:
    Pipe3(string str){
        this->origStr = str;
        this->setBoolVals();
    }

    virtual void execute() {
        if (!this->falseFlag) {
            if (this->third_isList) {
                Shell* ls = new ExecCommand(removeSpacesFrontNBack(third_str));
                ls->execute();
                return;
            }
            // third is not ls
            if (this->second_isList) {
                this->exec_skipFirst();
                return;
            }
            // second not ls
            this->exec_all();
            return;
        }
        return;
    }

    virtual void setBoolVals() {
        int pos = onePipePos(this->origStr);
        int tmp = 0;

        string c1_str = this->origStr.substr(0, pos);
        this->first_str = c1_str;

        tmp = pos;
        pos = onePipePos(this->origStr, pos);

        string c2_str = this->origStr.substr(tmp + 1, (pos - tmp - 1));
        this->second_str = c2_str;
        this->second_isList = (removeSpacesFrontNBack(second_str).substr(0, 2) == "ls");

        string c3_str = this->origStr.substr(pos + 1);
        this->third_str = c3_str;
        this->third_isList = (removeSpacesFrontNBack(third_str).substr(0, 2) == "ls");


        this->falseFlag = false;
        if (removeSpacesFrontNBack(c3_str) == "false") {
            cout << "return value is false" << endl;
            this->falseFlag = true;
        }
        this->exitFlag = false;

        if (removeSpacesFrontNBack(this->first_str) == "exit") {
            this->first_str = "false";
        }
        if (removeSpacesFrontNBack(this->second_str) == "exit") {
            this->second_str = "false";
        }
        if (removeSpacesFrontNBack(this->third_str) == "exit") {
            this->third_str = "false";
        }

        return;
    }

private:
    void exec_skipFirst() {
        int pos = onePipePos(this->origStr);
        int tmp = pos;
        pos = onePipePos(this->origStr, pos);

        int c2_argc = 0, c3_argc = 0, status;
        // cout << "exec_skipFirst" << endl;

//        string c2_str = this->origStr.substr(tmp + 1, (pos - tmp - 1));
        vector<string> c2_v = parseSpace(this->second_str);
        c2_argc = c2_v.size()+1;
        char* c2_args[c2_argc];   // leave a space for filename, a space for NULL

        // cout << "main c2_args:" << endl;
        for (int i = 0; i < c2_argc - 1; i++) {
            c2_args[i] = new char[c2_v.at(i).length() + 1];
            strcpy(c2_args[i], c2_v.at(i).c_str());
            // cout << c2_args[i] << endl;
        }
        // args2's no input file
        c2_args[c2_argc - 1] = NULL;

        // c3 args below
//        string c3_str = this->origStr.substr(pos + 1);
        vector<string> c3_v = parseSpace(this->third_str);
        c3_argc = c3_v.size()+2;
        char* c3_args[c3_argc];   // leave a space for filename

        // cout << "main c3_args:" << endl;
        for (int i = 0; i < c3_argc - 2; i++) {
            c3_args[i] = new char[c3_v.at(i).length() + 1];
            strcpy(c3_args[i], c3_v.at(i).c_str());
            // cout << c3_args[i] << endl;
        }
        // args3's file
        char file2[] = "  ";
        char* outFile2 = file2;
        c3_args[c3_argc - 2] = outFile2;
        c3_args[c3_argc - 1] = NULL;

        pid_t pid = 0;
        pid = fork();
        if (pid < 0) {
            perror("fork2()");
        }
        if (pid == 0) {
            int tmpfd2 = creat(outFile2, 0644);
            dup2(tmpfd2, STDOUT_FILENO);
            if(execvp(c2_args[0], c2_args) == -1) {
                perror("execvp()");
            }
        }

        while (wait(NULL) != pid){}
        pid = fork();
        if (pid < 0) {
            perror("fork2()");
        }
        if (pid == 0) {
            if (execvp(c3_args[0], c3_args) == -1) {
                perror("execvp()");
            }
        }

//    close(pipefd[READ]);
//    close(pipefd[WRITE]);

        // waitpid(-1, &status, 0);
        waitpid(-1, &status, 0);
        return;
        return;
    }
    void exec_all() {
        // cout << this->origStr << endl;
        int c1_argc = 0, c2_argc = 0, c3_argc = 0;

        // command 1 args prep
//       int pos = onePipePos(this->origStr);
//        // cout << "first pipe pos: " << pos << endl;
//        string c1_str = this->origStr.substr(0, pos);
        vector<string> c1_v = parseSpace(this->first_str);

        c1_argc = c1_v.size()+1;
        char* c1_args[c1_argc];

        // cout << "main c1_args:" << endl;
        for (int i = 0; i < c1_argc - 1; i++) {
            c1_args[i] = new char[c1_v.at(i).length() + 1];
            strcpy(c1_args[i], c1_v.at(i).c_str());
            // cout << c1_args[i] << endl;
        }
        c1_args[c1_v.size()] = NULL;

        // c2 args below:
//        int tmp = pos;
//        pos = onePipePos(this->origStr, pos);
//        // cout << "second pipe pos: " << pos << endl;
//        string c2_str = this->origStr.substr(tmp + 1, (pos - tmp - 1));
        vector<string> c2_v = parseSpace(this->second_str);
        c2_argc = c2_v.size()+2;
        char* c2_args[c2_argc];   // leave a space for filename, a space for NULL

        // cout << "main c2_args:" << endl;
        for (int i = 0; i < c2_argc - 2; i++) {
            c2_args[i] = new char[c2_v.at(i).length() + 1];
            strcpy(c2_args[i], c2_v.at(i).c_str());
            // cout << c2_args[i] << endl;
        }
        // args2's file
        char file1[] = " ";
        char* outFile1 = file1;
        c2_args[c2_argc - 2] = outFile1;
        c2_args[c2_argc - 1] = NULL;

        // c3 args below
//        string c3_str = this->origStr.substr(pos + 1);
        vector<string> c3_v = parseSpace(this->third_str);
        c3_argc = c3_v.size()+2;
        char* c3_args[c3_argc];   // leave a space for filename

        // cout << "main c3_args:" << endl;
        for (int i = 0; i < c3_argc - 2; i++) {
            c3_args[i] = new char[c3_v.at(i).length() + 1];
            strcpy(c3_args[i], c3_v.at(i).c_str());
            // cout << c3_args[i] << endl;
        }
        // args3's file
        char file2[] = "  ";
        char* outFile2 = file2;
        c3_args[c3_argc - 2] = outFile2;
        c3_args[c3_argc - 1] = NULL;
//=====================================
//    cout << "test print" << endl;
//
//    cout << "c1_argc: " << c1_argc << endl;
//    for (int i = 0; i < c1_argc - 1; i++) {
//        cout << c1_args[i] << " ";
//    }
//    if (c1_args[c1_argc - 1]) cout << c1_args[c1_argc - 1];
//    cout << endl;
//    // =========================================
//    cout << "c2_argc: " << c2_argc << endl;
//    for (int i = 0; i < c2_argc - 1; i++) {
//        cout << c2_args[i] << " ";
//    }
//    if (c2_args[c2_argc - 1]) cout << c2_args[c2_argc - 2];
//    cout << endl;
//    // =========================================
//    cout << "c3_argc: " << c3_argc << endl;
//    for (int i = 0; i < c3_argc - 1; i++) {
//        cout << c3_args[i] << " ";
//    }
//    if (c3_args[c3_argc - 1]) cout << c3_args[c3_argc - 2];
//    cout << endl;

        int status;
        pid_t pid;

        // first pipe write into file1,
        // second pipe use file1 as arg, write into file2
        // third pipe use file2 as arg, write to STDOUT

        int tmpfd1 = 0;
        int tmpfd2 = 0;
        // pipe(pipefd);

        pid = fork();
        if (pid < 0) {
            perror("fork()");
        }
        if (pid == 0) {
            // close(pipefd[READ]);
            tmpfd1 = creat(outFile1, 0644);
            dup2(tmpfd1, STDOUT_FILENO);
            if (execvp(c1_args[0], c1_args) == -1) {
                perror("execvp()");
            }
        }

        while (wait(NULL) != pid){}
        pid = fork();
        if (pid < 0) {
            perror("fork2()");
        }
        if (pid == 0) {
            tmpfd2 = creat(outFile2, 0644);
            dup2(tmpfd2, STDOUT_FILENO);
            if(execvp(c2_args[0], c2_args) == -1) {
                perror("execvp()");
            }
        }

        while (wait(NULL) != pid){}
        pid = fork();
        if (pid < 0) {
            perror("fork2()");
        }
        if (pid == 0) {
            if (execvp(c3_args[0], c3_args) == -1) {
                perror("execvp()");
            }
        }

//    close(pipefd[READ]);
//    close(pipefd[WRITE]);

        // waitpid(-1, &status, 0);
        waitpid(-1, &status, 0);
        return;
    }
};

#endif