//
// Created by Fangzhong Li on 12/11/19.
//

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <fstream>
#include "../header/classes/shell.hpp"
#include "../header/classes/execCommand.hpp"
#include "../header/classes/testCommand.hpp"
#include "../header/helper/redirection.hpp"
#include "../header/helper/parsePipe.hpp"
#include "../header/helper/identifyTestCommand.h"
#include "../header/helper/assembleFuntions.hpp"
#include "../header/helper/parseSpace.hpp"
#define READ 0
#define WRITE 1

int main(int argc, char** argv) {
    // argc[1] : "com1 | com2"
    string in = argv[1];
    // cout << in << endl;
    int c1_argc = 0, c2_argc = 0, c3_argc = 0;

    // command 1 args prep
    int pos = onePipePos(in);
    // cout << "first pipe pos: " << pos << endl;
    string c1_str = in.substr(0, pos);
    vector<string> c1_v = parseSpace(c1_str);

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
    int tmp = pos;
    pos = onePipePos(in, pos);
    // cout << "second pipe pos: " << pos << endl;
    string c2_str = in.substr(tmp + 1, (pos - tmp - 1));
    vector<string> c2_v = parseSpace(c2_str);
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
    string c3_str = in.substr(pos + 1);
    vector<string> c3_v = parseSpace(c3_str);
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
}
