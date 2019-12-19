//
// Created by Fangzhong Li on 11/26/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_SEMI_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_SEMI_TEST_H

#include <gtest/gtest.h>
#include "../header/classes/semi.hpp"
#include "../header/classes/shell.hpp"
#include "../header/classes/execCommand.hpp"
#include "../header/classes/testCommand.hpp"
#include "../header/classes/amp.hpp"
#include "../header/classes/pipe.hpp"

TEST (semiTest, t1) {
    Shell* c1 = new ExecCommand("ls -a");
    Shell* c2 = new TestCommand("[ hello ]");
    Shell* semi = new Semi(c1, c2);
    semi->execute();
    EXPECT_EQ(semi->isExit(), false);
    EXPECT_EQ(semi->isFalse(), true);
    EXPECT_EQ(semi->getFormalStr(), "ls -a ; [ -e hello ]");
}

TEST (semiTest, t2) {
    Shell* c1 = new ExecCommand("ls -a");
    Shell* c2 = new ExecCommand("exit");
    Shell* semi = new Semi(c1, c2);
    semi->execute();
    EXPECT_EQ(semi->isExit(), true);
    EXPECT_EQ(semi->isFalse(), true);
    EXPECT_EQ(semi->getFormalStr(), "ls -a ; exit");
}

TEST (semiTest, t3) {
    Shell* c1 = new ExecCommand("exit");
    Shell* c2 = new ExecCommand("ls");
    Shell* semi = new Semi(c1, c2);
    semi->execute();
    EXPECT_EQ(semi->isExit(), true);
    EXPECT_EQ(semi->isFalse(), true);
    EXPECT_EQ(semi->getFormalStr(), "exit ; ls");
}

TEST (semiTest, t4) {
    Shell* c1 = new ExecCommand("false");
    Shell* c2 = new ExecCommand("ls");
    Shell* semi = new Semi(c1, c2);
    semi->execute();
    EXPECT_EQ(semi->isExit(), false);
    EXPECT_EQ(semi->isFalse(), false);
    EXPECT_EQ(semi->getFormalStr(), "false ; ls");
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_SEMI_TEST_H
