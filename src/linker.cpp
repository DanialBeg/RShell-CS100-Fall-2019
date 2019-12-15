#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linker.hpp"

using namespace std;

Linker::Linker(){}

Linker::Linker(Command* l, Command* r){
    leftL = l;
    rightL = r;
}

// bool Linker::execute(){
//     bool ret = false;
//     Input* inp = new Input();
//     arguments = inp->parse_input(this->inputS);
//     connectors = inp->get_connectors(this->inputS);

//     for(int i = 0; i <connectors.size(); i++){
//         string ls = "";
//         string rs = "";

//         if(connectors.at(i) == "&&"){
//             for(unsigned i = 0; i < strlen(arguments[i]); i++){
//                 ls += arguments[i];
//             }
//             for(unsigned i = 0; i < strlen(arguments[i+1]); i++){
//                 rs += arguments[i];
//             }
//             Command* l = new Rshell(ls);
//             Command* r = new Rshell(rs);
//             this->leftL = l;
//             this->rightL = r;
//             And* andObj = new And(leftL, rightL);
//             ret = andObj->execute();
//         }
//         else if(connectors.at(i) == ";"){
//             for(unsigned i = 0; i < strlen(arguments[i]); i++){
//                 ls += arguments[i];
//             }
//             for(unsigned i = 0; i < strlen(arguments[i+1]); i++){
//                 rs += arguments[i];
//             }
//             Command* l = new Rshell(ls);
//             Command* r = new Rshell(rs);
//             this->leftL = l;
//             this->rightL = r;
//             Or* orObj = new Or(leftL, rightL);
//             ret = orObj->execute();
//         }
//         else if(connectors.at(i) == "||"){
//             for(unsigned i = 0; i < strlen(arguments[i]); i++){
//                 ls += arguments[i];
//             }
//             for(unsigned i = 0; i < strlen(arguments[i+1]); i++){
//                 rs += arguments[i];
//             }
//             Command* l = new Rshell(ls);
//             Command* r = new Rshell(rs);
//             this->leftL = l;
//             this->rightL = r;
//             Semicolon* semicolonObj = new Semicolon(leftL, rightL);
//             ret = semicolonObj->execute();
//         }
//     }
//     return ret;
// }
