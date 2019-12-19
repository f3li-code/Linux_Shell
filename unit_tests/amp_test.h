//
// Created by Fangzhong Li on 11/25/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_AMP_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_AMP_TEST_H

#include "../header/classes/execCommand.hpp"
#include "../header/classes/testCommand.hpp"
#include "../header/classes/amp.hpp"
#include <gtest/gtest.h>

TEST(ampTest, test1) {
    Shell* left = new ExecCommand("false");
    Shell* right = new ExecCommand("echo hello");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "false && echo hello");
    EXPECT_EQ(amp->isFalse(), true);
    EXPECT_EQ(amp->isExit(), false);
}

TEST(ampTest, test2) {
    Shell* left = new ExecCommand("exit");
    Shell* right = new ExecCommand("echo hello");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "exit && echo hello");
    EXPECT_EQ(amp->isExit(), true);
    EXPECT_EQ(amp->isFalse(), true);
}
TEST(ampTest, test3) {
    Shell* left = new ExecCommand("echo hello");
    Shell* right = new ExecCommand("false");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "echo hello && false");
    EXPECT_EQ(amp->isFalse(), true);
    EXPECT_EQ(amp->isExit(), false);
}

TEST(ampTest, test4) {
    cout << "true + exit" << endl;
    Shell* left = new ExecCommand("echo hello");
    Shell* right = new ExecCommand("exit");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "echo hello && exit");
    EXPECT_EQ(amp->isExit(), true);
    EXPECT_EQ(amp->isFalse(), true);
}

TEST(ampTest, test5) {
    Shell* left = new TestCommand("[ -d googletest ]");
    Shell* right = new ExecCommand("echo hello");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "[ -d googletest ] && echo hello");
    EXPECT_EQ(amp->isFalse(), false);
    EXPECT_EQ(amp->isExit(), false);
}

TEST(ampTest, test6) {
    Shell* left = new TestCommand("[ -d googletes ]");
    Shell* right = new ExecCommand("echo hello");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "[ -d googletes ] && echo hello");
    EXPECT_EQ(amp->isExit(), false);
    EXPECT_EQ(amp->isFalse(), true);
}

TEST(ampTest, test7) {
    Shell* left = new ExecCommand("false");
    Shell* right = new TestCommand("[ -d googletest ]");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "false && [ -d googletest ]");
    EXPECT_EQ(amp->isFalse(), true);
    EXPECT_EQ(amp->isExit(), false);
}

TEST(ampTest, test8) {
    Shell* left = new TestCommand("[ -d googletes ]");
    Shell* right = new ExecCommand("exit");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "[ -d googletes ] && exit");
    EXPECT_EQ(amp->isExit(), false);
    EXPECT_EQ(amp->isFalse(), true);
}

TEST(ampTest, test9) {
    cout << "exit + true" << endl;
    Shell* left = new ExecCommand("exit");
    Shell* right = new ExecCommand("ls");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "exit && ls");
    EXPECT_EQ(amp->isExit(), true);
    EXPECT_EQ(amp->isFalse(), true);
}

TEST(ampTest, test10) {
    cout << "exit + false" << endl;
    Shell* left = new ExecCommand("exit");
    Shell* right = new ExecCommand("false");
    Shell* amp = new Amp(left, right);
    amp->execute();
    EXPECT_EQ(amp->getOrigStr(), "exit && false");
    EXPECT_EQ(amp->isExit(), true);
    EXPECT_EQ(amp->isFalse(), true);
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_AMP_TEST_H
