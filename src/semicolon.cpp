#include "semicolon.hpp"
#include "linker.hpp"

using namespace std;

Semicolon::Semicolon():Linker(){}

Semicolon::Semicolon(Command* l, Command* r){
    this->leftL = l;
    this->rightL = r;
}

//  bool semicolonExecute(Command* l, Command* r){
//     bool retB = false;
//     l->execute();
//     retB = r->execute();
//     return retB;
// }

bool Semicolon::execute(){
    bool retB = false;
    this->leftL->execute();
    retB = this->rightL->execute();
    return retB;
}
