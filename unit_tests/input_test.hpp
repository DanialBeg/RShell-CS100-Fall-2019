#ifndef __INPUT_TEST_HPP__
#define __INPUT_TEST_HPP__

#include "gtest/gtest.h"

#include "../src/input.cpp"

using namespace std;

TEST(InputTest, ParseConnectorsNoQuotes) {
    Input* inp = new Input();
    string input = "echo hello || ls -la; mkdir bin/";
    vector<string> conns = inp->get_connectors(input);
    EXPECT_EQ(conns.at(0), "||");
    EXPECT_EQ(conns.at(1), ";");
}

TEST(InputTest, ParseCommandsNoQuotes) {
    Input* inp = new Input();
    string input = "echo hello || ls -la; mkdir bin/";
    vector<string> comms = inp->parse_input(input);
    EXPECT_EQ(comms.at(0), "echo hello");
    EXPECT_EQ(comms.at(1), "ls -la");
    EXPECT_EQ(comms.at(2), "mkdir bin/");
}

TEST(InputTest, ParseConnectorsWithQuotes) {
    Input* inp = new Input();
    string input = "echo \"hello \"t\"here;\" && ls -la; mkdir bin/";
    vector<string> conns = inp->get_connectors(input);
    EXPECT_EQ(conns.at(0), "&&");
    EXPECT_EQ(conns.at(1), ";");
}

TEST(InputTest, ParseCommandsWithQuotes) {
    Input* inp = new Input();
    string input = "echo \"hello \"there\";\" && ls -la; mkdir bin/";
    vector<string> comms = inp->parse_input(input);
    EXPECT_EQ(comms.at(0), "echo hello there;");
    EXPECT_EQ(comms.at(1), "ls -la");
    EXPECT_EQ(comms.at(2), "mkdir bin/");
}

#endif //__INPUT_TEST_HPP__
