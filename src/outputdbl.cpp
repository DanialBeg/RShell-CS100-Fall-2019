#include "outputdbl.hpp"
#include "linker.hpp"

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <fstream>

using namespace std;

OutputDirDbl::OutputDirDbl():Linker(){}

OutputDirDbl::OutputDirDbl(Command* l, Command* r){
    this->leftL = l;
    this->rightL = r;
}

OutputDirDbl::OutputDirDbl(Command* l){
    this->leftL = l;
}

bool OutputDirDbl::execute(){
    int num = dup(1);
    int file = open(fString.c_str(), O_CREAT | O_WRONLY |  O_APPEND, 0664);

    if(file == -1){
        perror("File error");
        retBool =  false;
    }
    else{
        close(1);
        dup2(file, 1);
        retBool = this->leftL->execute();

        close(1);
        dup2(num, 1);
    }
    
    return retBool;
}
