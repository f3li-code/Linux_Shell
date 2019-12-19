#include "../header/classes/shell.hpp"
#include "../header/helper/helperMain.hpp"
#include "../header/helper/assembleFuntions.hpp"

#include <iostream>
#include <string>

using namespace std;
int main(int argc, char** argv) {
    bool exitFlag = false;
    string input = "";
    // vector<string> commandLines;
    // vector<Shell*> commandObjs;
    Shell* root = NULL;

//    cout << "==================" << endl;
//    cout << "======RSHELL======" << endl;
//    cout << "==================" << endl;

    while (!exitFlag) {
        cout << "$ ";

        // modify raw input
        getline(cin, input);

        input = removePound(input);
        if (input == "") continue;

        if (!hasValidQuotes(input)) {
            cout << "invalid input: quotes" << endl;
            continue;
        }
        if (!hasValidParen(input)) {
            cout << "invalid input: parentheses" << endl;
            continue;
        }
        // build the tree
        root = assemble(input);

        if (root == NULL) {
            cout << "invalid input: NULL" << endl;
            continue;
        }
        // Execute from the root
        root->execute();

        // if no exit, then keep running
        exitFlag = root->isExit();
        if (exitFlag) {
            // cout << "exit is detected" << endl;
        }
    }

    return 0;
}