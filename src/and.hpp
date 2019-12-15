#ifndef __AND_HPP__
#define __AND_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

class And: public Linker{
    public:
        And();
        And(Command *l, Command* r);
        //virtual bool andExecute(Rshell* l, Rshell* r);
        virtual bool execute();
        bool ret;
        string s;
};

#endif //__AND_HPP__
