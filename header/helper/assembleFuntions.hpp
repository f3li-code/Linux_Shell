#ifndef __ASSEMBLEFUNCTIONS__
#define __ASSEMBLEFUNCTIONS__

#include "../classes/shell.hpp"
#include "../classes/execCommand.hpp"
#include "../classes/testCommand.hpp"
#include "../classes/amp.hpp"
#include "../classes/pipe.hpp"
#include "../classes/semi.hpp"
#include "../classes/redirectFactory.h"
#include "parseToWholeCommands.h" // parseToWholeCommand
#include "assembleHelper.h"
#include "identifyTestCommand.h"

//==================================================Thurs=======
#include "removeSpaceFrontNBack.h"
#include "redirection.hpp"      // bool isRedirecCom(str)
//==================================================Thurs=======
#include <vector>
#include <string>
#include <stack>

using namespace std;
Shell* buildCompoundCommand(string);
string removeSpacesFrontNBack(string);
vector <string> parseCompoundOps (string);
vector<Shell*> getCommands (string);
vector<string> getOps (string);
Shell* buildSemiStructure (vector<Shell*>);

Shell* assemble(string str) {
    //==================================================Thurs=======
    // int c = 0;
    //==================================================Thurs=======
    vector<string> com_strs = parseToWholeCommands(str);
    vector<Shell*> com_ptrs (com_strs.size(), NULL);
    if (com_strs.size() == 1 && com_strs.at(0) == "") return NULL;
    // cout << "in assemble" << endl;
    for (int i = 0; i < com_strs.size(); i++) {
        com_strs.at(i) = removeSpacesFrontNBack(com_strs.at(i));
        if (isParen(com_strs.at(i))) { // pare
            // cout << com_strs.at(i) << " is parenthese command" << endl;
            com_ptrs.at(i) = assemble(stripParen(com_strs.at(i)));
        } else {
            // cout << com_strs.at(i) << " not a parenthese command" << endl;
            //==================================================Thurs=======
            // cout << "whole command " << c << ") " << com_strs.at(i) << endl;
            // c++;
            //==================================================Thurs=======
            com_ptrs.at(i) = buildCompoundCommand(com_strs.at(i));
        }
    }
    return buildSemiStructure(com_ptrs);
}


vector <string> parseCompoundOps (string str) {
    vector<string> res;
    int start = 0;
    bool semiOpen = false;
    stack<char> parenSt;

    for (int i = 0; i < str.length() - 1; i++) {
        if (str[i] == '"') semiOpen = !semiOpen;
        if (str[i] == '(') parenSt.push('(');
        if (str[i] == ')') parenSt.pop();
        if (!semiOpen && parenSt.empty()) {
            if ((str[i] == '&' && str[i+1] == '&') || (str[i] == '|' && str[i+1] == '|')) {
                // cout << "in parseCompoundOps: push to commands: " << str.substr(start, (i - start)) << endl;
                res.push_back(removeSpacesFrontNBack(str.substr(start, (i - start))));
                // cout << "in parseCompoundOps: push to ops: " << str.substr(i, 2) << endl;
                res.push_back(removeSpacesFrontNBack(str.substr(i, 2)));
                i = i + 1;
                start = i + 1;
            }
        }
    }
    //cout << "in parseCompoundOps: push to commands: " << str.substr(start, (str.length() - start)) << endl;
    res.push_back(removeSpacesFrontNBack(str.substr(start, (str.length() - start))));
    return res;
}

vector<Shell*> getCommands (string str) {
    vector<string> target = parseCompoundOps(str);
    vector<Shell*> res;
    Shell* com = NULL;

    for (int i = 0; i < target.size(); i++) {
        if (target.at(i) != "&&" && target.at(i) != "||") {
            if (isParen(target.at(i))) {
                com = assemble(target.at(i));
            } else {
                if (isTest_str(target.at(i))) {
                    com = new TestCommand(target.at(i));
                    //==================================================Thurs=======
                } else if (isRedirectCom(target.at(i))){
                    // cout << "In getCommands: Found redirect command" << endl;
                    RedirectFactory* f = new RedirectFactory(target.at(i));
                    com = f->createCommand();

                    //==================================================Thurs=======
                } else {
                    com = new ExecCommand(target.at(i));
                }
            }
            res.push_back(com);
        }
    }

    return res;
}

vector<string> getOps (string str) {
    vector<string> target = parseCompoundOps(str);
    vector<string> ops;

    for (int i = 0; i < target.size(); i++) {
        if (target.at(i) == "&&" || target.at(i) == "||") {

            ops.push_back(target.at(i));
        }
    }

    return ops;
}

Shell* buildCompoundCommand (string str) {
    // cout << str << endl;
    vector<Shell*> commands = getCommands(str);
    for (int i = 0; i < commands.size(); i++) {
        // cout << commands.at(i)->getFormalStr() << endl;
    }
    if (commands.size() == 1) return commands.at(0);

    vector<string> ops = getOps(str);

    stack<Shell*> st;
    st.push(commands.at(0));
    int comVecP = 1;
    int opVecP = 0;
    Shell* l = NULL;
    Shell* r = NULL;
    Shell* compound = NULL;
    while (opVecP < ops.size()) {
        if (st.size() == 2) {
            r = st.top();
            st.pop();
            l = st.top();
            st.pop();
            if (ops.at(opVecP) == "&&") {
                compound = new Amp(l, r);
            } else {
                compound = new Pipe(l, r);
            }
            st.push(compound);
            opVecP++;
        } else {
            st.push(commands.at(comVecP));
            comVecP++;
        }
    }
    return st.top();
}

Shell* buildSemiStructure (vector<Shell*> commands) {

    stack<Shell*> st;
    Shell* newSemi = NULL;
    Shell* l = NULL;
    Shell* r = NULL;
    int i = 0;
    int size = commands.size();

    while (i < size) {
        if (st.size() != 2) {
            st.push(commands.at(i));
            i++;
        }
        if (st.size() == 2) {
            r = st.top();
            st.pop();
            l = st.top();
            st.pop();
            newSemi = new Semi(l, r);
            st.push(newSemi);
        }
    }
    return st.top();
}

#endif
