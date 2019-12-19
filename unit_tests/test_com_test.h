//
// Created by Fangzhong Li on 11/25/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_TEST_COM_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_TEST_COM_TEST_H

#include "../header/classes/testCommand.hpp"
#include <gtest/gtest.h>

TEST(testTest, test1) {
    Shell* t1 = new TestCommand("[ ./notes.txt ]");
    t1->execute();
    EXPECT_EQ(t1->getOrigStr(), "[ ./notes.txt ]");
    EXPECT_EQ(t1->getFormalStr(), "[ -e ./notes.txt ]");
}

TEST(testTest, test2) {
    Shell* t1 = new TestCommand("[ ./CMakeCache.txt ]");
    t1->execute();
    EXPECT_EQ(t1->getOrigStr(), "[ ./CMakeCache.txt ]");
    EXPECT_EQ(t1->getFormalStr(), "[ -e ./CMakeCache.txt ]");
}

TEST(testTest, test3) {
    Shell* t1 = new TestCommand("[ -d ./CMakeCache.txt ]");
    t1->execute();
    EXPECT_EQ(t1->getOrigStr(), "[ -d ./CMakeCache.txt ]");
    EXPECT_EQ(t1->getFormalStr(), "[ -d ./CMakeCache.txt ]");
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_TEST_COM_TEST_H
