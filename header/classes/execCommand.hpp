#ifndef __EXECCOMMAND_HPP__
#define __EXECCOMMAND_HPP__

#include "command.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#include "../helper/parseSpace.hpp"

/*
 * ==========
 * from inheritance
 * ==========
protected:
	bool falseFlag;
	bool exitFlag;
	string origStr;
    vector<string> words;      - FROM COMMAND

public:
	virtual void execute() = 0;
	virtual string getOrigStr() = 0
    virtual string getFormalStr() = 0;
    virtual void setBoolVals() = 0;

	bool isFalse() {
	    return this->falseFlag;
	}
	bool isExit () {
	    return this->exitFlag;
	}
 * =========
 * end inheritance
 * =========
 */

class ExecCommand : public Command {

private:
    bool invalid;
public:
	ExecCommand (string line) {
	    this->origStr = line;
	    this->words = parseSpace(line);
	    this->setBoolVals();
	}

	virtual void execute() {
	    if (this->invalid) {
	        cout << "error: invalid command, exit value set to false" << endl;
	        return;
	    }
	    if (this->isFalse() || this->isExit()) {
	 	    return;
	    }

	    char* args[this->words.size() + 1];
	
	    for (int i = 0; i < this->words.size(); i++) {
            // gets rid of potential quotes in PATH and executables
            if (this->words.at(i)[0] == '"') {
                this->words.at(i) = this->words.at(i).substr(1, this->words.at(i).length() - 1);
            }
            if (this->words.at(i)[this->words.at(i).length() - 1] == '"') {
                this->words.at(i) = this->words.at(i).substr(0, (this->words.at(i).length() - 1));
            }
            args[i] = (char*)this->words.at(i).c_str();
	    }
	    args[this->words.size()] = NULL;
		
	    // run with fork, wait execvp and perror
	    pid_t pid = fork();
	    if (pid == -1) {
		    perror("fork() error");
	    } else if (pid == 0) {
		    // child
		    if (execvp(args[0], args) == -1) {
                this->falseFlag = true;
                this->exitFlag = false;
                perror("execvp() error");
            }
		    exit(0);

		    //cout << "child ended" << endl;
	    } else if (pid > 0) {
		    // parent
		    while (wait(NULL) != pid){}
	    }
	    return;
	}

    virtual void setBoolVals() {
	    this->falseFlag = false;
	    this->exitFlag = false;
	    this->invalid = false;

	    if (this->words.at(0) == "") {
	        this->invalid = true;
	        this->falseFlag = true;
	        this->exitFlag = false;
	    }
	    if (this->words.at(0) == "false" || this->words.at(0) == "\"false\"") {
	        this->falseFlag = true;
	    }
	    if ((this->words.at(0) == "exit" || this->words.at(0) == "\"exit\"")) {
	        this->exitFlag = true;
	        this->falseFlag = true;
	    }
	    return;
	}
};

#endif
