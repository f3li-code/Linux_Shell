#ifndef __SEMI_HPP__
#define __SEMI_HPP__

#include "shell.hpp"
#include "operator.hpp"

class Semi : public Operator {
    // protected:
    	// bool status;
    	// Shell* leftCommand;
    	// Shell* rightCommand;
    // public:
    	// bool getStatus() { return this->status;}

    public:
	Semi (Shell* left, Shell* right) {
	    this->leftCommand = left;
	    this->rightCommand = right;
	    this->setBoolVals();
	}

	virtual void execute() {
	    this->leftCommand->execute();
	    if (!this->leftCommand->isExit()) {
	        this->rightCommand->execute();
	    }
	    return;
	}
	virtual void setBoolVals() {
	    this->falseFlag = false;
	    this->exitFlag = false;
	    if (this->leftCommand->isExit() || this->rightCommand->isExit()) {
	        this->exitFlag = true;
	        this->falseFlag = true;
	        return;
	    }
	    if (this->rightCommand->isFalse()) {
	        this->falseFlag = true;
	        return;
	    }
	    return;
	}

    virtual string getOrigStr() {
        return this->leftCommand->getOrigStr() + " ; " + this->rightCommand->getOrigStr();
    }
    virtual string getFormalStr() {
        return this->leftCommand->getFormalStr() + " ; " + this->rightCommand->getFormalStr();
    }
}; 

#endif
