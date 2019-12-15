#ifndef __PIPE_HPP__
#define __PIPE_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

class Pipe: public Linker{
    public:
        Pipe();
        Pipe(Command *l, Command* r);
        //virtual bool andExecute(Rshell* l, Rshell* r);
        virtual bool execute();
        bool retBool;
        int flag;
        char* charp;
};

#endif //__PIPE_HPP__
