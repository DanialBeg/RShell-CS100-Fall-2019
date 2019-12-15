#ifndef __PAREN_TEST_HPP__
#define __PAREN_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/rshell.cpp"

using namespace std;

TEST(ParenTest, OneCommandOneParenthesis) {

    std::string str = "(echo hello)";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(ParenTest, TwoCommandsOneParenthesis) {

    std::string str = "(echo hello && echo hi)";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(ParenTest, OneCommandTwoParentheses) {

    std::string str = "(echo hello) && (echo hi)";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(ParenTest, TwoCommandsTwoParentheses) {

    std::string str = "(echo hello || echo hi) && (echo bye || echo goodbye)";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(ParenTest, TestAndParenthesis) {

    std::string str = "[ -e and_test.hpp ] && (echp passed || echo success)";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

#endif //__PAREN_TEST_HPP__
