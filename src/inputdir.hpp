#ifndef __IN_HPP__
#define __IN_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

class InputDir: public Linker{
    public:
        InputDir();
        InputDir(Command *l, Command* r);
        InputDir(Command *l);
        //virtual bool andExecute(Rshell* l, Rshell* r);
        virtual bool execute();
        bool retBool;
};

#endif //__IN_HPP__
