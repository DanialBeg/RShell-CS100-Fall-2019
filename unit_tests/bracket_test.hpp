#ifndef __BRACKET_TEST_HPP__
#define __BRACKET_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/rshell.cpp"

using namespace std;

TEST(BracketTest, ExistsTest) {

    std::string str = "[ -e and_test.hpp ]";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(BracketTest, DirectoryTest) {

    std::string str = "[ -d ../src ]";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(BracketTest, RegularTest) {

    std::string str = "[ -f and_test.hpp ]";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

#endif //__TEST_TEST_HPP__
