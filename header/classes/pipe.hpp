#ifndef __PIPE_HPP
#define __PIPE_HPP

#include "shell.hpp"
#include "operator.hpp"

class Pipe : public Operator {
    // protected:
        // bool status;
        // bool power;
        // Shell* leftCommand;
        // Shell* rightCommand;
    
   // public:
   	// bool getStatus() { return this->status;}
	// bool getPower() {return this->power;}

    public:
	Pipe (Shell* leftCommand, Shell* rightCommand) {
	    this->leftCommand = leftCommand;
	    this->rightCommand = rightCommand;
	    this->setBoolVals();
	}
                      
	virtual void execute() {
	    // cout << "executing PIPE: " << this->getFormalStr() << endl;

	    this->leftCommand->execute();
	    if (this->leftCommand->isFalse() && !this->leftCommand->isExit()) {
	        this->rightCommand->execute();
	    }
	    return;
 	}

 	virtual void setBoolVals() {
	    this->falseFlag = false;
	    this->exitFlag = false;
        if (this->leftCommand->isExit() || (this->leftCommand->isFalse() && !this->leftCommand->isExit() && this->rightCommand->isExit())) {
            this->falseFlag = true;
            this->exitFlag = true;
            return;
        }
        if (this->leftCommand->isFalse() && !this->leftCommand->isExit() && this->rightCommand->isFalse() && !this->rightCommand->isExit()) {
            this->falseFlag = true;
            return;
        }
	}

    virtual string getOrigStr() {
        return this->leftCommand->getOrigStr() + " || " + this->rightCommand->getOrigStr();
    }
    virtual string getFormalStr() {
        return this->leftCommand->getFormalStr() + " || " + this->rightCommand->getFormalStr();
    }
};

#endif
