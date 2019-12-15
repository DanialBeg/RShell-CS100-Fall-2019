#ifndef __OR_TEST_HPP__
#define __OR_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/rshell.hpp"

TEST(OrTest, CommandAndCommand) {

    std::string str = "echo hello || ls -la";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}

TEST(OrTest, CommandAndCommand1) {

    std::string str = "ls -la || w";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}

TEST(OrTest, CommandAndCommand2) {

    std::string str = "ls || mkdir bin/";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}

#endif //__OR_TEST_HPP__
