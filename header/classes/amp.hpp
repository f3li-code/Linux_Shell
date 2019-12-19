#ifndef __AMP_HPP__
#define __AMP_HPP__

#include "shell.hpp"
#include "operator.hpp"

class Amp : public Operator {
    // protected:
    	// bool status;
    	// bool power;
    	// Shell* leftCommand;
    	// Shell* rightCommand;

    // public:
    	// bool getStatus() {return this->status;}
	// bool isOn() {return this->power;}

    public:
	Amp(Shell* left, Shell* right) {
	    this->leftCommand = left;
	    this->rightCommand = right;
	    this->setBoolVals();
	}
	
	virtual void execute() {
	   // cout << "executing AMP: " << this->getFormalStr() << endl;

	   this->leftCommand->execute();
	   if (!this->leftCommand->isFalse()) {
	       this->rightCommand->execute();
	   }
	   return;
	}

	virtual void setBoolVals() {
	    this->exitFlag = false;
	    this->falseFlag = false;
	    if (this->leftCommand->isExit() || (!this->leftCommand->isFalse() && this->rightCommand->isExit())) { // done
	        this->exitFlag = true;
	        this->falseFlag = true;
	        return;
	    }
	    if ((!this->leftCommand->isFalse() && this->rightCommand->isFalse() && !this->rightCommand->isExit())
	        || (this->leftCommand->isFalse() && !this->leftCommand->isExit())) { // done
	        this->falseFlag = true;
	        return;
	    }
	}

	virtual string getOrigStr() {
	    return this->leftCommand->getOrigStr() + " && " + this->rightCommand->getOrigStr();
	}
	virtual string getFormalStr() {
	    return this->leftCommand->getFormalStr() + " && " + this->rightCommand->getFormalStr();
	}
};

#endif
