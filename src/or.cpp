#include "or.hpp"
#include "linker.hpp"

using namespace std;

Or::Or():Linker(){}

Or::Or(Command* l, Command* r){
    this->leftL = l;
    this->rightL = r;
}

// bool orExecute(Command* l, Command* r){
//     bool retB = false;
//     if(l->execute() == false){
//         retB = r->execute();
//     }
//     else{
//         retB = false;
//     }
//     return retB;
// }

bool Or::execute(){
    bool retB = true;
    if(this->leftL->execute() == false){
        retB = this->rightL->execute();
    }
    else{
        //cout << "No need" << endl;
        return true;
    }
    return retB;
}
