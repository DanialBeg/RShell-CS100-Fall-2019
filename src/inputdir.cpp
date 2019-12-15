#include "inputdir.hpp"
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

InputDir::InputDir():Linker(){}

InputDir::InputDir(Command* l, Command* r){
    this->leftL = l;
    this->rightL = r;
}

InputDir::InputDir(Command* l){
    this->leftL = l;
}

bool InputDir::execute(){
    int num = dup(0);
    int file = open(fString.c_str(), O_RDWR, 0664);

    if(file == -1){
        perror("File error");
        retBool =  false;
    }
    else{
        close(0);
        dup2(file, 0);
        retBool = this->leftL->execute();

        close(0);
        dup2(num, 0);
    }
    
    return retBool;
}
