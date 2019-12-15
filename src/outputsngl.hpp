#ifndef __OS_HPP__
#define __OS_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

class OutputDirSingle: public Linker{
    public:
        OutputDirSingle();
        OutputDirSingle(Command *l, Command* r);
        OutputDirSingle(Command *l);
        virtual bool execute();
        bool retBool;
};

#endif //__OS_HPP__
