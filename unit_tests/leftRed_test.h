//
// Created by Fangzhong Li on 12/12/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_LEFTRED_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_LEFTRED_TEST_H
#include <gtest/gtest.h>
#include "../header/classes/leftRed.hpp"
#include "../header/classes/execCommand.hpp"

TEST(left, t1) {
    Shell* c1 = new LeftRed("cat < new.txt");
    EXPECT_EQ(c1->getOrigStr(), "cat < new.txt");

    c1->execute();
}
#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_LEFTRED_TEST_H
