#include "../header/classes/shell.hpp"
#include "../header/helper/helperMain.hpp"
#include "../header/helper/assembleFuntions.hpp"

#include <iostream>
#include <string>


using namespace std;

int main(int argc, char** argv) {
    bool exitFlag = false;
    Shell* root;
    string input = "";
    for (int i = 1; i < argc; i++) {
	input = input + " " + argv[i];
    }

    cout << "$ " << input << endl;

    input = removePound(input);
    if (input == "")

    if (!hasValidQuotes(input)) {
        cout << "invalid input: quotes" << endl;
    }
    if (!hasValidParen(input)) {
        cout << "invalid input: parentheses" << endl;
    }
    // build the tree
    root = assemble(input);

    if (root == NULL) {
        cout << "invalid input: NULL" << endl;
    }
    // Execute from the root
    root->execute();
    // if no exit, then keep running
    exitFlag = root->isExit();
    if (exitFlag) cout << "exited shell" << endl;
    else cout << "shell still running" << endl;
    return 0;
}
