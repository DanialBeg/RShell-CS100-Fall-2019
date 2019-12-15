#ifndef __CMD_HPP__
#define __CMD_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Command{
    protected:
        // vector<string> arguments;
        //string inputS;
    public:
      /* Constructors*/
        // Command(){};

        // Command(string s) : inputS(s) {};

        // Command(string command_type, vector<string> arguments) :
        //         command_type(command_type), arguments(arguments) {};


        // string get_command_type() {
        //     return this->inputS;
        // }
        // void set_command_type(string command_type) {
        //     this->command_type = command_type;
        // }
        //
        // vector<string> get_arguments() {
        //   return this->arguments;
        // }
        virtual bool execute() = 0;
        bool test_flag;
        string fString;
        string lString;
        char* charp;
        char* charl;
        char* charr;
        // void set_arguments(vector<string> arguments) {
        //   this->arguments = arguments;
        // }

};

#endif //__CMD_HPP__
