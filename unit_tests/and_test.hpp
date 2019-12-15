#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/linker.cpp"
#include "../src/rshell.cpp"
#include "../src/and.cpp"

using namespace std;

TEST(AndTest, CommandAndCommand) {

    std::string str = "echo hello && ls -la";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

TEST(AndTest, CommandAndCommand1) {

    std::string str = "w && ls -la";
    char * ch = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), ch);
    ch[str.size()] = '\0';

    Rshell* link = new Rshell(ch);

    EXPECT_TRUE(link->execute());
}

// TEST(AndTest, ErrorAndCommand) {
//
//     std::string strL = "w";
//     std::string strR = "pss -a";
//
//     // int maxlen = -1;
//     // if(strL.length() > strR.length()){
//     //     maxlen = strL.length();
//     // }
//     // else{
//     //     maxlen = strR.length();
//     // }
//
//     // char* chL = new char[maxlen+1];
//     // for(int i =0; i<maxlen; i++){
//     //     chL[i] = strL.at(i);
//     // }
//
//     // char* chR = new char[maxlen+1];
//     // for(int i =0; i<maxlen; i++){
//     //     chR[i] = strR.at(i);
//     // }
//
//     char * chL = new char[strL.size() + 1];
//     std::copy(strL.begin(), strL.end(), chL);
//     chL[strL.size()] = '\0';
//
//     char * chR = new char[strR.size() + 1];
//     std::copy(strR.begin(), strR.end(), chR);
//     chR[strR.size()] = '\0';
//
//     Command* left = new Rshell(chL);
//     Command* right = new Rshell(chR);
//     And* andObj = new And(left, right);
//     bool ret = andObj->execute();
//     cout << "Return is " << andObj->ret << endl;
//
//      EXPECT_EQ(andObj->ret, false);
// }

// TEST(AndTest, ErrorAndError) {
//
//     std::string str = "echp hello && paa";
//     char * ch = new char[str.size() + 1];
//     std::copy(str.begin(), str.end(), ch);
//     ch[str.size()] = '\0';
//
//     Rshell* link = new Rshell(ch);
//
//     EXPECT_FALSE(link->execute());
// }

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


#endif //__AND_TEST_HPP__

/* https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char */
