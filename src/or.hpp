#ifndef __OR_HPP__
#define __OR_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

class Or: public Linker{
    public:
        Or(Command* l, Command* r);
        Or();
        //virtual bool orExecute(Command* l, Command* r);
        virtual bool execute();
};

#endif //__OR_HPP__
