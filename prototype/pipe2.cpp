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

    int pos = onePipePos(in);
    // command 1 args prep
    string c1_str = in.substr(0, pos);
    vector<string> c1_v = parseSpace(c1_str);
    char* c1_args[c1_v.size()+1];

    // cout << "main c1_args:" << endl;
    for (int i = 0; i < c1_v.size(); i++) {
        c1_args[i] = new char[c1_v.at(i).length() + 1];
        strcpy(c1_args[i], c1_v.at(i).c_str());
        // cout << c1_args[i] << endl;
    }
    c1_args[c1_v.size()] = NULL;

    // c2 args below:
    string c2_str = in.substr(pos + 1);
    vector<string> c2_v = parseSpace(c2_str);

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

    return 0;
}
