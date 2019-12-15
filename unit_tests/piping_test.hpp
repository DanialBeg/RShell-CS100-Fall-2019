#ifndef __PIPING_TEST_HPP__
#define __PIPING_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/rshell.hpp"

TEST(PipingTest, PipingTestOne) {

    std::string str = "ls -la | master";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}

TEST(PipingTest, PipingTestTwo) {

    std::string str = "ls -la | more";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}


#endif //__PIPING_TEST_HPP__
