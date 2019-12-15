#ifndef __REDIRECT_TEST_HPP__
#define __REDIRECT_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/rshell.hpp"

TEST(RedirectTest, InputRedirect) {

    std::string str = "cat < echo \"Hello There\"";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}

TEST(RedirectTest, OutputRedirect) {

    std::string str = "(echo ls && echo mkdir) > output.txt";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}

TEST(RedirectTest, OutputDoubleRedirect) {

    std::string str = "(echo hello && echo there) >> output.txt";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_EQ(link->execute(), true);
}


#endif //__REDIRECT_TEST_HPP__
