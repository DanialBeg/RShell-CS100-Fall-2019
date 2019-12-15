#include "and.hpp"
#include "linker.hpp"

using namespace std;

And::And():Linker(){}

And::And(Command* l, Command* r){
    this->leftL = l;
    this->rightL = r;
}

bool And::execute(){
    bool retB = false;
    if(this->leftL->execute() == true){
        retB = this->rightL->execute();
    }
    else{
        rightL = NULL;
        retB = false;
    }
    ret = retB;
    //cout << "Return for And is " << retB << endl;
    return retB;
}
