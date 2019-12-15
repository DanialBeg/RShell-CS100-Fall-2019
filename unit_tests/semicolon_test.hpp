#ifndef __SEMICOLON_TEST_HPP__
#define __SEMICOLON_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/rshell.hpp"
#include "../src/semicolon.cpp"

TEST(SemicolonTest, CommandAndCommand1) {

    std::string str = "echo hello; ls -la";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}

TEST(SemicolonTest, CommandAndCommand2) {

    std::string str = "echo hello; ls";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}


#endif //__SEMICOLON_TEST_HPP__
