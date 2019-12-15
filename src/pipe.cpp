#include "pipe.hpp"
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

Pipe::Pipe():Linker(){}

Pipe::Pipe(Command* l, Command* r){
    flag = -1;
    this->leftL = l;
    this->rightL = r;
}

bool Pipe::execute(){
    int pNum[2];
    retBool = true;

    if(pipe(pNum) == -1){
        perror("Piping Error");
        retBool = false;
        return retBool;
    }

    int wr = pNum[1];
    int rd = pNum[0];

    int temp = dup(1);
    dup2(wr, 1);

    bool left = leftL->execute();
    if(left == false){
        return false;
    }
    dup2(temp, 1);
    close(wr);

    temp = dup(0);
    dup2(rd, 0);

    bool right = rightL->execute();
    if(right == false){
        //cout << "Right is false" << endl;
        return false;
    }
    //cout << "What is RD: " << rd << endl;
    dup2(temp, 0);
    close(rd);

    return retBool;
}
