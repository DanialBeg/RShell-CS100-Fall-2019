    #include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "command.hpp"
#include "rshell.cpp"
#include "rshell.hpp"
#include "inputdir.hpp"
#include "outputsngl.hpp"
#include "outputdbl.hpp"
#include "pipe.hpp"
//#include "input.hpp"
#include "and.cpp"
#include "or.cpp"
#include "semicolon.cpp"
#include "linker.cpp"
#include "inputdir.cpp"
#include "outputsngl.cpp"
#include "outputdbl.cpp"
#include "pipe.cpp"

using namespace std;
using namespace boost;

vector<string> parse(string input) {
    //cout << "Before tokenizing: " << input << endl;
    vector<string> vect;

    typedef tokenizer<char_separator<char> > tokenizer;

    escaped_list_separator<char> els("", "&&||;#()[]<>",  "\"\"");
    boost::tokenizer<escaped_list_separator<char> > tok(input, els);

    for(boost::tokenizer<escaped_list_separator<char> >::iterator beg = tok.begin();
        beg != tok.end(); ++beg) {

        string tmp(*beg);

        boost::trim(tmp);
        if (!tmp.empty()) {
            vect.push_back(tmp);
            //cout << "<"<< tmp << ">" << endl;
        }
    }

    //const_cast<char*> learned from classmate Hugo Contreras
    char** ch = new char*[vect.size() + 1];
    for (int i = 0; i < vect.size(); i++) {
        ch[i] = const_cast<char*>(vect.at(i).c_str());
    }

    return vect;
}

//FUNCTION: trims input of spaces and extra quotes to count connectors
string trim_input(string input) {
    string split;

    escaped_list_separator<char> els2("", "\"",  " ");
    boost::tokenizer<escaped_list_separator<char> > tok2(input, els2);

    for(boost::tokenizer<escaped_list_separator<char> >::iterator beg = tok2.begin();
        beg != tok2.end(); beg++) {
        string tmp(*beg);
        split += (tmp);
    }

    return split;
}

//FUNCTION: Counts connectors in given input, excluding quoted arguments
vector<string> getconn(string input) {

    string split = "";

    split = input;
    // cout << split << endl;

    string token = "", connector = "";
    vector<string> vect_tokens;

    for (int i = 0; i < split.length(); i++) {

      char c = split[i];
      if (c == '#') {
          connector += c;
          vect_tokens.push_back(connector);
          connector = "";
          break;
      }
      else if (c == '\"') {
          i++;
          while (split[i] != '\"') {
            i++;
          }
      }
      else if (c == '(' || c == ')') {
          connector += c;
          vect_tokens.push_back(connector);
          connector = "";
      }
      else if (c == '[' || c == ']') {
          connector += c;
          vect_tokens.push_back(connector);
          connector = "";
      }
      else if (c == ';') {
        connector += c;
        vect_tokens.push_back(connector);
        connector = "";
      }
      else if (c == '<') {
        connector += c;
        vect_tokens.push_back(connector);
        connector = "";
      }
      else if (c == '&') {
          connector += c;
          if (split[i + 1] == '&' ) {
            connector += c;
            i++;
          }
          vect_tokens.push_back(connector);
          connector = "";
      }
      else if (c == '|') {
          connector += c;
          if (split[i + 1] == '|' ) {
            connector += c;
            i++;
          }
          vect_tokens.push_back(connector);
          connector = "";
      }
      else if (c == '>') {
        connector += c;
        if (split[i + 1] == '>' ) {
          connector += c;
          i++;
        }
        vect_tokens.push_back(connector);
        connector = "";
      }
    }
    return vect_tokens;
}

vector<int> get_test_indices(vector<string> args) {
    vector<int> ret;
    for (int i = 0; i < args.size(); i++) {
        if (args.at(i).size() > 3) {
            if (args.at(i).substr(0, 5) == "test ") {
                ret.push_back(i);
            }
        }
    }
    return ret;
}

int main(int argc, char** argv) {
    string input = "";
    int cFlag = -1;
    bool exitStatus = false;

    //cout << "Testing "<< argc << endl;

    if(argc > 1){
        for(int i = 1; i<argc; i++){
            input += argv[i];
            input += ' ';
        }
    }

    while (!exitStatus) {
        int testF = -1;
        cout << "$ ";
        if (argc < 2){
            getline(cin, input);
        }
        //argc = 0;
        //cout << input << endl;

        // if (input == "exit" || input == "Exit"){
        //     exitStatus = true;
        //     exit(0);
        // }
        // Input* inp = new Input();
        //char** arguments = new char*[strlen(parse(input)[0])];
        vector<string> args = parse(input);
        vector<string> connectors = getconn(input);

        vector<int> ind = get_test_indices(args);

        for(int i = 0; i < ind.size(); i++){
            testF = 1;
            if(connectors.size() > 0){
                //cout << "Testing" << endl;
                connectors.insert(connectors.begin()+i, 1, "[");
                connectors.insert(connectors.begin()+i+1, 1, "]");
            }
            else{
                connectors.push_back("[");
                connectors.push_back("]");
            }
        }

        // for(int i = 0; i < connectors.size(); i++){
        //     if(i != 0 && (connectors.at(i) == ">" || connectors.at(i) == "<"
        //         || connectors.at(i) == ">>")){
        //         cout << "Did something" << endl;
        //         connectors.insert(connectors.begin()+i, 1, "(");
        //         connectors.insert(connectors.begin()+i+1, 1, ")");
        //     }
        // }

        char** arguments = new char*[args.size()];
        for (int i = 0; i < args.size(); i++) {
            arguments[i] = const_cast<char*>(args.at(i).c_str());
        }

        if(connectors.empty() || connectors.at(0) == "#"){
            string s = "";

            if(input != "" && input != " " && input != "  "  && input.at(0) != '#'){
                Rshell* o = new Rshell(arguments[0]);
                o->execute();
            }
        }

        else if(connectors.size() > 0){
            int paran = 0;
            Command* l;
            Command* r;

            Command* prev;
            Command* pip;
            Command* outSing;
            Command* tempPrev;
            Command* andObj;
            Command* semicolonObj;
            Command* orObj;
            Command* next;
            Command* inp;
            int flag = -1;
            int parenFlag = -1;
            int dupCount = 0;
            int cnt = 0;

            for(int i = 0; i <connectors.size(); i++){
                int ifFlag = -1;
                string ls = "";
                string rs = "";

                if(connectors.at(i) == "("){
                    if(i > 0){
                        if(connectors.at(i-1) != "("){
                            paran += 1;
                        }
                        else{
                            parenFlag = 1;
                            dupCount += 1;
                        }
                    }
                    else{
                        paran += 1;
                    }

                    if(connectors.at(i+1) == ")"){
                        if(input != "" && input != " " && input != "  "  && input.at(0) != '#'){
                            Command* o = new Rshell(arguments[cnt]);
                            prev = o;
                            cnt += 1;
                        }
                    }
                }
                else if (connectors.at(i) == ")"){
                    paran += 1;
                    if(flag == 0){
                        andObj = new And(tempPrev, prev);
                        prev = andObj;
                    }
                    else if(flag == 1){
                        semicolonObj = new Semicolon(tempPrev, prev);
                        prev = semicolonObj;
                    }
                    else if(flag == 2){
                        orObj = new Or(tempPrev, prev);
                        prev = orObj;
                    }
                    flag = -1;
                    cFlag = -1;
                }
                else if (connectors.at(i) == "["){
                    //cout << "Went into here" << endl;
                    if (testF == -1){
                        //cout << "Index: " << (i-(paran+dupCount)) << endl;
                        Command* bracket = new Rshell(arguments[(i-(paran+dupCount))], true);
                        cnt += 1;
                        prev = bracket;
                        paran += 1;
                    }
                    else if(testF == 1){
                        //cout << "Args: " << arguments[0][0] << endl;
                        int indexA = (i-(paran+dupCount));
                        //cout << "Index: " << (i-(paran+dupCount)) << endl;
                        int len = strlen(arguments[(i-(paran+dupCount))]);
                        char* temp = new char[len-4];
                        for(int i = 4; i < len; i++){
                            temp[i-4] = arguments[indexA][i];
                        }
                        arguments[indexA] = temp;
                        //cout << "Args: " << arguments[(i-(paran+dupCount))] << endl;
                        Command* bracket = new Rshell(arguments[(i-(paran+dupCount))], true);
                        cnt += 1;
                        prev = bracket;
                        paran += 1;
                    }
                    cFlag = -1;
                    //cout << "Args: " << arguments[i] << endl;
                }
                else if (connectors.at(i) == "]"){
                    paran += 1;
                    if(flag == 3){
                        andObj = new And(tempPrev, prev);
                        prev = andObj;
                    }
                    else if(flag == 4){
                        semicolonObj = new Semicolon(tempPrev, prev);
                        prev = semicolonObj;
                    }
                    else if(flag == 5){
                        orObj = new Or(tempPrev, prev);
                        prev = orObj;
                    }
                    flag = -1;
                    cFlag = -1;
                }
                else if(connectors.at(i) == "&&"){
                    if(i == 0 || (paran != 0 && paran%2 != 0)){
                        if (parenFlag == 1){
                            //cout << "Left: " << arguments[(i-(paran+dupCount))] << endl;
                            //cout << "Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                            l = new Rshell(arguments[(i-(paran+dupCount))]);
                            r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                            l->charp = arguments[i-(paran+dupCount)];
                            r->charp = arguments[(i-(paran+dupCount)) + 1];
                            andObj = new And(l, r);
                            prev = andObj;
                        }
                        else if(i < connectors.size() -1 && i == 0){
                            if(connectors.at(i+1) == "("){
                                flag = 0;
                                l = new Rshell(arguments[i-paran]);
                                prev = l;
                                tempPrev = prev;
                            }
                            else if(parenFlag == -1){
                                //cout << "Left: " << arguments[i-paran] << endl;
                                //cout << "Right: " << arguments[(i-paran)+1] << endl;
                                l = new Rshell(arguments[i-paran]);
                                r = new Rshell(arguments[(i-paran)+1]);
                                andObj = new And(l, r);
                                prev = andObj;
                            }
                        }
                        else if(parenFlag == -1){
                            //cout << "Left: " << arguments[i-paran] << endl;
                            //cout << "Right: " << arguments[(i-paran)+1] << endl;
                            l = new Rshell(arguments[i-paran]);
                            r = new Rshell(arguments[(i-paran)+1]);
                            andObj = new And(l, r);
                            prev = andObj;
                        }
                        ifFlag = 1;
                    }
                    else if (ifFlag == -1){
                        if (i < connectors.size()-1){
                            if(connectors.at(i+1) == "("){
                                flag = 0;
                                tempPrev = prev;
                            }
                            else if (connectors.at(i+1) == "["){
                                flag = 3;
                                tempPrev = prev;
                            }
                            else{
                                Command* rs = new Rshell(arguments[(i-(paran+dupCount))+1]);
                                andObj = new And(prev, rs);
                                prev = andObj;
                            }
                        }
                        else{
                            Command* rs = new Rshell(arguments[(i-(paran+dupCount))+1]);
                            andObj = new And(prev, rs);
                            prev = andObj;
                        }
                    }
                    cFlag = -1;
                }

                else if(connectors.at(i) == "#") {
                    // Command* l = new Rshell(arguments[i-paran]);
                    // prev = l;
                    i = connectors.size();
                    cFlag = -1;
                }

                else if(connectors.at(i) == ";"){
                    if(i == 0 || (paran != 0 && paran%2 != 0)){
                        if (parenFlag == 1){
                            //cout << "Left: " << arguments[(i-(paran+dupCount))] << endl;
                            //cout << "Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                            l = new Rshell(arguments[(i-(paran+dupCount))]);
                            r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                            l->charp = arguments[i-(paran+dupCount)];
                            r->charp = arguments[(i-(paran+dupCount)) + 1];
                            semicolonObj = new Semicolon(l, r);
                            prev = semicolonObj;
                        }
                         else if(i < connectors.size() -1 && i == 0){
                            if(connectors.at(i+1) == "("){
                                flag = 1;
                                l = new Rshell(arguments[i-paran]);
                                prev = l;
                                tempPrev = prev;
                            }
                            else if(parenFlag == -1){
                                //cout << "Left: " << arguments[i-paran] << endl;
                                //cout << "Right: " << arguments[(i-paran)+1] << endl;
                                l = new Rshell(arguments[i-paran]);
                                r = new Rshell(arguments[(i-paran)+1]);
                                semicolonObj = new Semicolon(l, r);
                                prev = semicolonObj;
                            }
                        }
                        else if(parenFlag == -1){
                            //cout << "Left: " << arguments[i-paran] << endl;
                            //cout << "Right: " << arguments[(i-paran)+1] << endl;
                            l = new Rshell(arguments[i-paran]);
                            r = new Rshell(arguments[(i-paran)+1]);
                            semicolonObj = new Semicolon(l, r);
                            prev = semicolonObj;
                        }
                        ifFlag = 1;
                    }
                    else if (ifFlag == -1){
                        if (i < connectors.size()-1){
                            if(connectors.at(i+1) == "("){
                                flag = 1;
                                tempPrev = prev;
                            }
                            else if(connectors.at(i+1) == "["){
                                flag = 4;
                                tempPrev = prev;
                            }
                            else{
                                Command* rs = new Rshell(arguments[(i-(paran+dupCount))+1]);
                                semicolonObj = new Semicolon(prev, rs);
                                prev = semicolonObj;
                            }
                        }
                        else{
                            Command* rs = new Rshell(arguments[(i-(paran+dupCount))+1]);
                            semicolonObj = new Semicolon(prev, rs);
                            prev = semicolonObj;
                        }
                    }
                    cFlag = -1;
                }
                else if(connectors.at(i) == "||"){
                    if(i == 0 || (paran != 0 && paran%2 != 0)){
                        if (parenFlag == 1){
                            //cout << "Left: " << arguments[(i-(paran+dupCount))] << endl;
                            //cout << "Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                            l = new Rshell(arguments[(i-(paran+dupCount))]);
                            r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                            l->charp = arguments[i-(paran+dupCount)];
                            r->charp = arguments[(i-(paran+dupCount)) + 1];
                            orObj = new Or(l, r);
                            prev = orObj;
                        }
                         else if(i < connectors.size() -1 && i == 0){
                            if(connectors.at(i+1) == "("){
                                flag = 2;
                                l = new Rshell(arguments[i-paran]);
                                prev = l;
                                tempPrev = prev;
                            }
                            else if(parenFlag == -1){
                                //cout << "Left: " << arguments[i-paran] << endl;
                                //cout << "Right: " << arguments[(i-paran)+1] << endl;
                                l = new Rshell(arguments[i-paran]);
                                r = new Rshell(arguments[(i-paran)+1]);
                                orObj = new Or(l, r);
                                prev = andObj;
                            }
                        }
                        else if(parenFlag == -1){
                            //cout << "Left: " << arguments[i-paran] << endl;
                            //cout << "Right: " << arguments[(i-paran)+1] << endl;
                            l = new Rshell(arguments[i-paran]);
                            r = new Rshell(arguments[(i-paran)+1]);
                            orObj = new Or(l, r);
                            prev = orObj;
                        }
                        ifFlag = 1;
                    }
                    else if (ifFlag == -1){
                        if (i < connectors.size()-1){
                            if(connectors.at(i+1) == "("){
                                flag = 2;
                                tempPrev = prev;
                            }
                            else if(connectors.at(i+1) == "["){
                                flag = 5;
                                tempPrev = prev;
                            }
                            else{
                                Command* rs = new Rshell(arguments[(i-(paran+dupCount))+1]);
                                orObj = new Or(prev, rs);
                                prev = orObj;
                            }
                        }
                        else{
                            Command* rs = new Rshell(arguments[(i-(paran+dupCount))+1]);
                            orObj = new Or(prev, rs);
                            prev = orObj;
                        }
                    }
                    cFlag = -1;
                }
                else if(connectors.at(i) == "<"){
                    if(i == 0 || (paran != 0 && paran%2 != 0)){
                        l = new Rshell(arguments[(i-(paran+dupCount))]);
                        l->test_flag = false;
                        l->charp = arguments[i-(paran+dupCount)];

                        outSing = new InputDir(l);

                        outSing->fString = arguments[(i-(paran+dupCount)) + 1];
                        prev = outSing;
                        prev->charl = l->charp;
                    }
                    else if(ifFlag == -1){
                        cout << "Prev here" << endl;
                        prev->test_flag = false;

                        outSing = new OutputDirSingle(prev);
                        outSing->fString = arguments[(i-(paran+dupCount)) + 1];
                        prev = outSing;
                    }
                    cFlag = -1;
                }
                else if(connectors.at(i) == ">"){
                    if(i == 0 || (paran != 0 && paran%2 != 0)){
                        //cout << "We are executing > right now" << endl;
                        //cout << arguments[(i-(paran+dupCount))] << endl;
                        l = new Rshell(arguments[(i-(paran+dupCount))]);
                        l->test_flag = false;
                        l->charp = arguments[i-(paran+dupCount)];
                        //r->charp = arguments[(i-(paran+dupCount)) + 1];
                        //r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                        //r->test_flag = false;
                        //cout << "Testing Left: " << arguments[(i-(paran+dupCount))] << endl;

                        outSing = new OutputDirSingle(l);
                        //cout << "Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                        outSing->fString = arguments[(i-(paran+dupCount)) + 1];
                        prev = outSing;
                        prev->charl = l->charp;
                    }
                    else if(ifFlag == -1){
                        // cout << "We are executing > right now" << endl;
                        // cout << arguments[(i-(paran+dupCount))] << endl;
                        //l = new Rshell(arguments[(i-(paran+dupCount))]);
                        prev->test_flag = false;
                        //r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                        //r->test_flag = false;
                        //cout << "Testing Left: " << arguments[(i-(paran+dupCount))] << endl;

                        outSing = new OutputDirSingle(prev);
                        //cout << "Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                        outSing->fString = arguments[(i-(paran+dupCount)) + 1];
                        prev = outSing;
                    }
                    cFlag = -1;
                }
                else if(connectors.at(i) == ">>"){
                    if(i == 0 || (paran != 0 && paran%2 != 0)){
                        //cout << "We are executing > right now" << endl;
                        //cout << arguments[(i-(paran+dupCount))] << endl;
                        l = new Rshell(arguments[(i-(paran+dupCount))]);
                        l->charp = arguments[i-(paran+dupCount)];
                        //r->charp = arguments[(i-(paran+dupCount)) + 1];
                        l->test_flag = false;
                        //r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                        //r->test_flag = false;
                        //cout << "Testing Left: " << arguments[(i-(paran+dupCount))] << endl;

                        outSing = new OutputDirDbl(l);
                        //cout << "Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                        outSing->fString = arguments[(i-(paran+dupCount)) + 1];
                        prev = outSing;
                    }
                    else if(ifFlag == -1){
                        //l = new Rshell(prev);
                        prev->test_flag = false;
                        //r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                        //r->test_flag = false;
                        //cout << "Testing Left: " << arguments[(i-(paran+dupCount))] << endl;

                        outSing = new OutputDirDbl(prev);
                        //cout << "Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                        outSing->fString = arguments[(i-(paran+dupCount)) + 1];
                        prev = outSing;
                    }
                    cFlag = -1;
                }
                else if(connectors.at(i) == "|"){
                    if(i == 0 || (paran != 0 && paran%2 != 0)){
                        l = new Rshell(arguments[i-(paran+dupCount)]);
                        r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                        // cout << "Left: " << arguments[i-(paran+dupCount)] << endl;
                        // cout << "Right: " << arguments[(i-(paran+dupCount))+1] << endl;
                        l->charp = arguments[i-(paran+dupCount)];
                        r->charp = arguments[(i-(paran+dupCount)) + 1];
                        pip = new Pipe(l, r);
                        prev = pip;
                        //prev->execute();
                        ifFlag = 1;
                    }
                    else if (ifFlag == -1){
                        //prev->execute();
                        //cout << "Checking Right: " << arguments[(i-(paran+dupCount)) + 1] << endl;
                        r = new Rshell(arguments[(i-(paran+dupCount)) + 1]);
                        if(cFlag == 1){
                            prev->charp = prev->charl;
                            //cout << "Checking left: " << prev->charp << endl;
                        }
                        else{
                            prev->charp = prev->charr;
                        }
                        r->charp = arguments[(i-(paran+dupCount)) + 1];
                        pip = new Pipe(prev, r);
                        prev = pip;
                    }
                }
            }
            prev->execute();
        }
    }

}
