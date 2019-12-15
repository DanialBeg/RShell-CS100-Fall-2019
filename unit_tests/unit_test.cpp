#include "gtest/gtest.h"

#include "and_test.hpp"
#include "semicolon_test.hpp"
#include "or_test.hpp"
#include "input_test.hpp"
#include "redirect_test.hpp"
#include "piping_test.hpp"
// #include "paren_test.hpp"
// #include "bracket_test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
