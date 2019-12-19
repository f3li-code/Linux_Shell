//
// Created by Fangzhong Li on 12/12/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_REDIRECTFACTORY_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_REDIRECTFACTORY_H

#include "leftRed.hpp"
#include "pipe2.hpp"
#include "pipe3.hpp"
#include "r_rightRed.hpp"
#include "redirect.hpp"
#include "rightRed.hpp"
#include "../helper/redirection.hpp"

class RedirectFactory{
private:
    string input;
    string type;

public:
    RedirectFactory(string str) {
        this->input = str;
    }

    Shell* createCommand() {
        if (this->input.find('<') != string::npos) return this->create_left();
        if (this->input.find(">>") != string::npos) return this->create_rRight();
        if (this->input.find('>') != string::npos) return this->create_right();

        if (this->input.find('|') != string::npos) {
            int pos = onePipePos(this->input);
            int tmp = pos;
            if (onePipePos(this->input, pos) == -1) {
                return this->create_p2();
            }
            else
                return this->create_p3();
        }
        return nullptr;
    }

private:
    Shell* create_left() {
        return new LeftRed(this->input);
    }
    Shell* create_right() {
        return new RightRed(this->input);
    }
    Shell* create_rRight() {
        return new R_RightRed(this->input);
    }
    Shell* create_p2() {
        return new Pipe2(this->input);
    }
    Shell* create_p3() {
        return new Pipe3(this->input);
    }
};


#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_REDIRECTFACTORY_H
