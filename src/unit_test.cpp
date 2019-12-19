#include "gtest/gtest.h"

/*
 #include "../header/helper/parseSpace.hpp"
 #include "../unit_tests/parseSpace_test.hpp"
 #include "../header/helper/helperMain.hpp"
 #include "../unit_tests/helperMain_test.hpp"
 #include "../header/helper/helperMain.hpp"


#include "../header/classes/execCommand.hpp"
#include "../unit_tests/exec_com_test.h"
#include "../header/classes/testCommand.hpp"
#include "../unit_tests/test_com_test.h"
#include "../header/classes/amp.hpp"
#include "../unit_tests/amp_test.h"
#include "../header/classes/pipe.hpp"
#include "../unit_tests/pipe_test.h"
#include "../header/classes/semi.hpp"
#include "../unit_tests/semi_test.h"
#include "../header/helper/parseToWholeCommands.h"
#include "../unit_tests/parseToWholeCommand_test.h"
*/

#include "../unit_tests/rightRed_test.h"
#include "../unit_tests/rRightRed_test.h"
#include "../unit_tests/leftRed_test.h"
#include "../unit_tests/pipe2_test.h"
#include "../unit_tests/pipe3_test.h"
// #include "../unit_tests/redirection_test.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

