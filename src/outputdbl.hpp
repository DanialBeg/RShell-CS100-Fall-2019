#ifndef __OD_HPP__
#define __OD_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

class OutputDirDbl: public Linker{
    public:
        OutputDirDbl();
        OutputDirDbl(Command *l, Command* r);
        OutputDirDbl(Command *l);
        //virtual bool andExecute(Rshell* l, Rshell* r);
        virtual bool execute();
        bool retBool;
};

#endif //__OD_HPP__
