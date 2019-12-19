//
// Created by Fangzhong Li on 12/12/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE3_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE3_TEST_H
#include <gtest/gtest.h>
#include "../header/classes/pipe2.hpp"
#include "../header/classes/pipe3.hpp"
#include "../header/classes/execCommand.hpp"
#include "../header/classes/rightRed.hpp"

TEST(pipe3, t1) {
    Shell* c1 = new Pipe3("ls | exit | wc");
    EXPECT_EQ(c1->getOrigStr(), "ls | exit | wc");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}

TEST(pipe3, t2) {
    Shell* c1 = new Pipe3("false | ls -a | wc");
    EXPECT_EQ(c1->getOrigStr(), "false | ls -a | wc");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}

TEST(pipe3, t2_ext) {
    Shell* c1 = new Pipe2("ls -a | wc");
    c1->execute();
}

TEST(pipe3, t3) {
    Shell* c1 = new Pipe3("false | false | wc");
    EXPECT_EQ(c1->getOrigStr(), "false | false | wc");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}

TEST(pipe3, t4) {
    Shell* c1 = new Pipe3("false | ls | false");
    EXPECT_EQ(c1->getOrigStr(), "false | ls | false");
    EXPECT_EQ(c1->isFalse(), true);

    c1->execute();
}

TEST(pipe3, t5) {
    Shell* c1 = new Pipe3("false | wc | ls -a");
    EXPECT_EQ(c1->getOrigStr(), "false | wc | ls -a");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}


TEST(pipe3, t6) {
    Shell* c1 = new Pipe3("false | ls -a | exit");
    EXPECT_EQ(c1->getOrigStr(), "false | ls -a | exit");
    EXPECT_EQ(c1->isFalse(), false);

    c1->execute();
}

//TEST(pipe3, t7) {
//    Shell* write = new RightRed("echo hello > new.txt");
//    write->execute();
//    Shell* c1 = new Pipe3("cat new.txt | tr A-Z a-z | tr a-z A-Z");
//    EXPECT_EQ(c1->getOrigStr(), "cat new.txt | tr A-Z a-z | tr a-z A-Z");
//    EXPECT_EQ(c1->isFalse(), false);
//
//    c1->execute();
//}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_PIPE3_TEST_H
