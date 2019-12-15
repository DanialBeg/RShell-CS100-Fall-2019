#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "rshell.hpp"

//#include "input.cpp"
// #include "and.hpp"
// #include "or.hpp"
// #include "semicolon.hpp"

using namespace std;
using namespace boost;

Rshell::Rshell(char* c){
    this->charp = c;
    this->test_flag = false;
    //inputS = s;
}

Rshell::Rshell(char* c, bool t){
    this->charp = c;
    this->test_flag = t;
    //inputS = s;
}

bool Rshell::execute(){
    if (test_flag == true) {
        return test();
    }
    else {
        return exec();
    }

}


// Rshell::Rshell(string input, vector<string> connector, char** argument){
//     this->inputS = input;
//     this->connectors = connector;
//     this->arguments = argument;
// }
vector<string> Rshell::split_by_space(char* inp) {
    vector<string> ret;
    string input(inp);

    escaped_list_separator<char> els("", " ",  "");
    boost::tokenizer<escaped_list_separator<char> > space_tok(input, els);

    for(boost::tokenizer<escaped_list_separator<char> >::iterator beg = space_tok.begin();
        beg != space_tok.end(); ++beg) {

        string tmp(*beg);

        boost::trim(tmp);
        if (!tmp.empty()) {
            ret.push_back(tmp);
            // cout << "<"<< tmp << ">" << endl;
        }
    }
    return ret;
}

bool Rshell::test() {
    struct stat sb;
    bool exists = false, is_dir = false, is_reg = false;
    bool status = true;
    string test_input;

    // cout << args.at(i) << endl;
    vector<string> test_args = split_by_space(this->charp);
    // cout << test_args.size() << endl;

    if (test_args.at(0) == "-f")
        is_reg = true;
    if (test_args.at(0) == "-d")
        is_dir = true;
    if (test_args.at(0) == "-e")
        exists = true;

    // cout << "stat: " << stat(test_args.at(1).c_str(), &sb) << endl;
    if (!exists && !is_dir && !is_reg) {
        test_input = test_args.at(0);
    }
    else {
        test_input = test_args.at(1);
    }

    if (stat(test_input.c_str(), &sb) == -1) {
        cout << "(False)" << endl;
        return false;
    }
    else {

        if (is_dir) {
            // cout << "ISDIR: "<< S_ISDIR(sb.st_mode) << endl;
            if (S_ISDIR(sb.st_mode) == 0)
                status = false;
        }

        if (is_reg) {
            // cout << "ISREG: " << S_ISREG(sb.st_mode) << endl;
            if (S_ISREG(sb.st_mode) == 0)
                status = false;
        }

        // cout << "STATUS: " << status << endl;

        if (status) {
            cout << "(True)" << endl;
            return true;
        }
    }
    return false;
}

bool Rshell::exec() {
    char* out = this->charp;

    //cout << (void*)(charp) << endl;
    //cout << "Testing execute rshell " << out[0] << endl;

    char* tempChar = new char[strlen(out)];
    char* args[100];
    tempChar = charp;
    int whitespace_pos = -1;
    string s = "";

    //cout << "Checking char*" << endl;
    // for(unsigned i = 0; i < strlen(charp); i++){
    //     //cout << tempChar[i];
    // }

    for(unsigned i = 0; i < strlen(charp); i++){
        if(tempChar[i] == ' '){
            whitespace_pos = i;
            i = strlen(charp);
        }
        s += tempChar[i];
    }
    if (s == "exit" || s=="Exit" || s=="EXIT"){
        exit(EXIT_SUCCESS);
    }
    //cout << s;
    args[0] = (char*)s.c_str();

    //cout << "Testing args[0]" << whitespace_pos << endl;

    string o = "";

    if(whitespace_pos == -1){
        //cout << "Index 0" << tempChar[0] << endl;
        args[1] = NULL;
    }
    else{
        for(unsigned j = 1; j < strlen(args); i++){
            o = "";
            for(unsigned i = whitespace_pos+1; i < strlen(charp); i++){
                if(tempChar[i] == ' '){
                    whitespace_pos = i;
                    i = strlen(charp);
                }
                //o += tempChar[i];
            }
            cout << "O is: " << o << endl;
            args[j] = (char*) o.c_str();
            // for(unsigned k = j; i < strlen(charp); i++){
            //     if(tempChar[i] == ' '){
            //         whitespace_pos = i;
            //         i = strlen(charp);
            //     }
            //     s += tempChar[i];
            // }
        }
    }

    bool retBool = true;

    pid_t pidt = fork();
    if(pidt == 0){
        int check = execvp(args[0], args);
        if (check < 0){
            retBool = false;
            perror("The command failed to execute");
        }
    }
    else if (pidt == -1){
        //if(errno){
        perror("Fork failed");
        // }
        retBool = false;
    }
    else if(pidt > 0){
        int stat;
        if (waitpid(pidt, &stat, 0) == -1){
            //if(errno){
            perror("Waiting on child process");
            //}
        }
    }
    //delete[] tempChar;
    return retBool;
}

// void Rshell::executeConnectors(){
//     //bool ret = false;
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
//             And* andObj = new And(l, r);
//             andObj->execute();
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
//             Or* orObj = new Or(l, r);
//             orObj->execute();
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
//             Semicolon* semicolonObj = new Semicolon(l, r);
//             semicolonObj->execute();
//         }
//     }
// }
