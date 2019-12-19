# Linux Shell

## Overview
* This program is a mimic of the Linux shell
* Supports commands in /bin with execvp
* Supports connectors (&& || ;)
* Supports parenthesizing of commands
* Supports piping and redirection
* The sequence will terminate when "exit" command is executed.

## Design Pattern
### Composite Pattern
* Shell class: An abstract class that has pure virtual functions: **execute()** and **print()** (for clearity and debugging).
* Composite: **Operator class**. **Amp, Pipe, and Semi classes** inherit from Operator class. Operators class all have a **vector of Base references**.
* Leaf: **Command class**, **TestCommand and ExecCommand**. Command class is the superclass of TestCommand and ExecCommand, executing a test command and a non-test command, respectively.
* Both **Operator class** and **Command class** inherit from **Shell class**.
### Factory Pattern
* **RedirectFactory class**: A concrete class that takes in a command string in the constructor and creates input redirection, output redirection, or piping based on the input string
* **redirection class**: An abstract class that is the super class of all the redirection subclasses
* **leftRedirection class**: A concrete class that performs input redirection
* **rightRed class**: A concrete class that performs output redirection (>)
* **r_rightRed class**: A concrete class that performs output redirection (>>)
* **pipe2 class**: A concrete class that performs the piping of two commands
* **pipe3 class**: A concrete class that performs the piping of three commands

# Diagram

![](https://user-images.githubusercontent.com/55297099/71199503-f0237000-224a-11ea-87f8-511ca344bf30.png)

note: to view integration tests
* Go into ./src. Do: g++ integTest.cpp -std=c++11 -o integ
* Go into ./integration_tests. Do: ./(insert test file here)
