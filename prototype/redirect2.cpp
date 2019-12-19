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

using namespace std;
int main(int argc, char* argv[]) {
    /*
     *  ./dup "ls > new.txt"
     */
    // argv0, argv1, argv2, argv3
    // args0, args1
    // input should be: "command > filepath"
    string in = argv[1];
    string command = in.substr(0, twoGreaterPos(in));
    string filename = removeSpacesFrontNBack(in.substr(twoGreaterPos(in) + 2));
    cout << "COMMAND: " << command << endl;
    cout << "FILE: " << filename << endl;
    char* output = new char[filename.length() + 1];
    strcpy(output, filename.c_str());

    vector<string> v = parseSpace(command);
    char* args [v.size() + 1];
    for (int i = 0; i < v.size(); i++) {
        args[i] = new char[v.at(i).length() + 1];
        strcpy(args[i], v.at(i).c_str());
    }
    args[v.size()] = NULL;

    //============
    int pipefd[2];
    char buf;
    pipe(pipefd);
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
    }
    if (pid == 0) {
        int ofd = open(output, O_APPEND | O_WRONLY);
        dup2(ofd, STDOUT_FILENO);
        execvp(args[0], args);
    }
    while (wait(NULL) != pid){}

    return 0;
}