//
// Created by Fangzhong Li on 11/25/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_EXEC_COM_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_EXEC_COM_TEST_H

#include "../header/classes/shell.hpp"
#include "../header/classes/execCommand.hpp"
#include <gtest/gtest.h>

TEST(execTest, test1) {
    Shell* c1 = new ExecCommand("ls");
    c1->execute();
    string a = c1->getFormalStr();
    EXPECT_EQ(a, "ls");
}

TEST(execTest, test2) {
    Command* c1 = new ExecCommand("   ls -a");
    c1->execute();
    string a = c1->getFormalStr();
    EXPECT_EQ(a, "ls -a");
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_EXEC_COM_TEST_H
