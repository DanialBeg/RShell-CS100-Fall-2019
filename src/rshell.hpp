#ifndef __RSHELL_HPP__
#define __RSHELL_HPP__

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "command.hpp"

using namespace std;

class Rshell: public Command{
    private:
        //vector<string> connectors;
        //char** arguments;
        
        //int pos;
        //string inputS;

        /* helper function for test() */
        vector<string> split_by_space(char* );
        bool test();
        bool exec();
        string sname;

    public:
        Rshell(){};
        Rshell(char* c);
        Rshell(char* c, bool t);
        //Rshell(string input, vector<string> connector, char** argument);
        //void executeConnectors();
        virtual bool execute();
};

#endif //__RSHELL_HPP__
