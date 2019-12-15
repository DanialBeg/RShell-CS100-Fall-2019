#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

class Semicolon: public Linker{
    public:
        Semicolon();
        Semicolon (Command* l, Command* r);
        //virtual bool semicolonExecute(Command* l, Command* r);
        virtual bool execute();
        
};

#endif //__SEMICOLON_HPP__