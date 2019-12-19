//
// Created by Fangzhong Li on 12/12/19.
//

#ifndef ASSIGNMENT_NO_HYPHEN_ALLOWED_RRIGHTRED_TEST_H
#define ASSIGNMENT_NO_HYPHEN_ALLOWED_RRIGHTRED_TEST_H
#include <gtest/gtest.h>
#include "../header/classes/r_rightRed.hpp"
#include "../header/classes/execCommand.hpp"

TEST(right_right, t1) {
    Shell* c1 = new R_RightRed("ls >> new.txt");
    Shell* c2 = new ExecCommand("cat new.txt");
    EXPECT_EQ(c1->getOrigStr(), "ls >> new.txt");

    c1->execute();
    c2->execute();
}

#endif //ASSIGNMENT_NO_HYPHEN_ALLOWED_RRIGHTRED_TEST_H
