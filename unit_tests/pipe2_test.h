//
// Created by Fangzhong Li on 12/12/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE2_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE2_TEST_H
#include <gtest/gtest.h>
#include "../header/classes/pipe2.hpp"
#include "../header/classes/execCommand.hpp"

TEST(pipe2, t1) {
    Shell* c1 = new Pipe2("ls | cut -b 1-5");
    EXPECT_EQ(c1->getOrigStr(), "ls | cut -b 1-5");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}

TEST(pipe2, t2) {
    Shell* c1 = new Pipe2("ls | false");
    EXPECT_EQ(c1->getOrigStr(), "ls | false");
    EXPECT_EQ(c1->isFalse(), true);

    c1->execute();
}

TEST(pipe2, t3) {
    Shell* c1 = new Pipe2("false | false");
    EXPECT_EQ(c1->getOrigStr(), "false | false");
    EXPECT_EQ(c1->isFalse(), true);

    c1->execute();
}

TEST(pipe2, t4) {
    Shell* c1 = new Pipe2("false | wc");
    EXPECT_EQ(c1->getOrigStr(), "false | wc");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}
TEST(pipe2, t5) {
    Shell* c1 = new Pipe2("exit | ls -a");
    EXPECT_EQ(c1->getOrigStr(), "exit | ls -a");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}
TEST(pipe2, t6) {
    Shell* c1 = new Pipe2("exit | exit");
    EXPECT_EQ(c1->getOrigStr(), "exit | exit");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}

TEST(pipe2, t7) {
    Shell* c1 = new Pipe2("exit | false");
    EXPECT_EQ(c1->getOrigStr(), "exit | false");
    EXPECT_EQ(c1->isFalse(), true);

    c1->execute();
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE2_TEST_H
