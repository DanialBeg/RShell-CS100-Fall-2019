#ifndef __EXIT_TEST_HPP__
#define __EXIT_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/linker.cpp"
#include "../src/rshell.cpp"
//#include "../src/and.cpp"

using namespace std;

TEST(ExitTest, Exit) {

    std::string str = "exit";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(ExitTest, ExitCmd) {
    std::string str = "ls-la exit";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

#endif //__AND_TEST_HPP__

/* https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char */
