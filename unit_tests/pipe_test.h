//
// Created by Fangzhong Li on 11/25/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE_TEST_H

#include "../header/classes/execCommand.hpp"
#include "../header/classes/testCommand.hpp"
#include "../header/classes/pipe.hpp"
#include "../header/classes/amp.hpp"
#include <gtest/gtest.h>

TEST (pipeTest, test1) {
    cout << "true + true" << endl;
    Shell* c1 = new ExecCommand("ls -a");
    Shell* c2 = new ExecCommand("echo hello");
    Shell* p = new Pipe(c1, c2);
    p->execute();
    EXPECT_EQ(p->getFormalStr(), "ls -a || echo hello");
    EXPECT_EQ(p->isFalse(), false);
    EXPECT_EQ(p->isExit(), false);
}

TEST (pipeTest, test2) {
    cout << "false + true" << endl;
    Shell* c1 = new TestCommand("test -e abc");
    Shell* c2 = new TestCommand("test     rshell");
    Shell* p = new Pipe(c1, c2);
    p->execute();
    EXPECT_EQ(p->getFormalStr(), "test -e abc || test -e rshell");
    EXPECT_EQ(p->isFalse(), false);
    EXPECT_EQ(p->isExit(), false);
}

TEST (pipeTest, test3) {
    cout << "true + exit" << endl;
    Shell* c1 = new ExecCommand("ls");
    Shell* c2 = new TestCommand("test     rshell");
    Shell* a = new Amp(c1, c2);
    Shell* c3 = new ExecCommand("exit");
    Shell* p = new Pipe(a, c3);
    p->execute();
    EXPECT_EQ(p->getFormalStr(), "ls && test -e rshell || exit");
    EXPECT_EQ(p->isFalse(), false);
    EXPECT_EQ(p->isExit(), false);
}

TEST (pipeTest, test4) {
    cout << "false + exit" << endl;
    Shell* c1 = new ExecCommand("ls");
    Shell* c2 = new TestCommand("test    -d rshell");
    Shell* a = new Amp(c1, c2);
    Shell* c3 = new ExecCommand("exit");
    Shell* p = new Pipe(a, c3);
    p->execute();
    EXPECT_EQ(p->getFormalStr(), "ls && test -d rshell || exit");
    EXPECT_EQ(p->isFalse(), true);
    EXPECT_EQ(p->isExit(), true);
}

TEST (pipeTest, test5) {
    cout << "false + false" << endl;
    Shell* c1 = new ExecCommand("ls");
    Shell* c2 = new TestCommand("test    -d rshell");
    Shell* a = new Amp(c1, c2);
    Shell* c3 = new ExecCommand("false");
    Shell* p = new Pipe(a, c3);
    p->execute();
    EXPECT_EQ(p->getFormalStr(), "ls && test -d rshell || false");
    EXPECT_EQ(p->isFalse(), true);
    EXPECT_EQ(p->isExit(), false);
}

TEST (pipeTest, test6) {
    cout << "exit + false" << endl;
    Shell* c1 = new ExecCommand("exit");
    Shell* c2 = new TestCommand("test    -d rshell");
    Shell* a = new Amp(c1, c2);
    Shell* c3 = new ExecCommand("false");
    Shell* p = new Pipe(a, c3);
    p->execute();
    EXPECT_EQ(a->isExit(), true);
    cout << "=======" << endl;
    EXPECT_EQ(p->getFormalStr(), "exit && test -d rshell || false");
    EXPECT_EQ(p->isFalse(), true);
    EXPECT_EQ(p->isExit(), true);
}

#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE_TEST_H
