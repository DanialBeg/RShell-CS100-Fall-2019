#ifndef __LINKER_HPP__
#define __LINKER_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "command.hpp"
//#include "rshell.hpp"

using namespace std;

class Linker: public Command{
    protected:
        Command* leftL;
        Command* rightL;
        // vector<string> connectors;
        // char** arguments;
        // string inputS;
    public:
        Linker(Command* l, Command* r);
        Linker();
        // Linker(string s){
        //     this->inputS = s;
        // };
        virtual bool execute() = 0;
        // virtual bool orExecute(Rshell* l, Rshell* r){};
        // virtual bool andExecute(Rshell* l, Rshell* r){};
        // virtual bool semicolonExecute(Rshell* l, Rshell* r){};
        //virtual ~Linker(){};
};

#endif //__LINKER_HPP__
