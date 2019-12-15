#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "command.hpp"
#include "rshell.cpp"
#include "rshell.hpp"
//#include "input.hpp"
#include "and.cpp"
#include "or.cpp"
#include "semicolon.cpp"
#include "linker.cpp"

using namespace std;
using namespace boost;

vector<string> parse(string input) {
    //cout << "Before tokenizing: " << input << endl;
    vector<string> vect;

    typedef tokenizer<char_separator<char> > tokenizer;

    escaped_list_separator<char> els("", "&&||;#()[]",  "\"\"");
    boost::tokenizer<escaped_list_separator<char> > tok(input, els);

    for(boost::tokenizer<escaped_list_separator<char> >::iterator beg = tok.begin();
        beg != tok.end(); ++beg) {

        string tmp(*beg);

        boost::trim(tmp);
        if (!tmp.empty()) {
            vect.push_back(tmp);
            cout << "<"<< tmp << ">" << endl;
        }
    }

    //const_cast<char*> learned from classmate Hugo Contreras
    // char** ch = new char*[vect.size() + 1];
    // for (int i = 0; i < vect.size(); i++) {
    //     ch[i] = const_cast<char*>(vect.at(i).c_str());
    // }

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
    }
    return vect_tokens;
}

vector<string> split_by_space(string input) {
    vector<string> ret;

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

int main(int argc, char** argv) {
    string input = "";
    bool exitStatus = false;

    //cout << "Testing "<< argc << endl;

    if(argc > 1){
        for(int i = 1; i<argc; i++){
            input += argv[i];
            input += ' ';
        }
    }

    while (!exitStatus) {
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

        //cout << "Testing if right" << endl;
        // for(int i =0; i<args.size(); i++){
        //     cout << args.at(i) << endl;
        // }

        char** arguments = new char*[args.size()];
        for (int i = 0; i < args.size(); i++) {
            arguments[i] = const_cast<char*>(args.at(i).c_str());
        }
        // cout << "Line 1: ";
        // cout << ch[0] << endl;

        //cout << connectors.size() << endl;
        //cout << "Testing args size : " << sizeof(arguments) << endl;
        //cout << "Testing args[1] : " << arguments[1] << endl;

        //Rshell* r = new Rshell(input, connectors, arguments);

        if(connectors.empty() || connectors.at(0) == "#"){
            string s = "";
            // for(int i = 0; i <strlen(arguments[0]); i++){
            //     s += arguments[0][i];
            // }
            //cout << s << endl;
            //cout << "Argument array: " << (void*)(arguments[0]) << endl;
            //Rshell* o = new Rshell(s, 0);
            //cout << "Testing " << arguments[0] << endl;
            //cout << "Input " << input.at(0) << endl;

            if(input != "" && input != " " && input != "  "  && input.at(0) != '#'){
                Rshell* o = new Rshell(arguments[0]);
                o->execute();
            }

            //cout << "test" << endl;
        }

        else if(connectors.size() > 0){
            int paran = 0;
            for(int i = 0; i <connectors.size(); i++){
                string ls = "";
                string rs = "";

                if(connectors.at(i) == "("){

                    if(connectors.at(i+1) == ")"){
                        if(input != "" && input != " " && input != "  "  && input.at(0) != '#'){
                            //cout << arguments[i] << " this is the input" << endl;
                            Rshell* o = new Rshell(arguments[i]);
                            o->execute();
                        }
                    }
                    paran += 1;
                }
                else if(connectors.at(i) == "&&"){
                    cout << "Testing string: " << i << " " << arguments[i] << endl;
                    Command* l = new Rshell(arguments[i-paran]);
                    Command* r = new Rshell(arguments[(i-paran)+1]);
                    And* andObj = new And(l, r);
                    andObj->execute();
                    // Command* l = new Rshell(ls, i);
                    // Command* r = new Rshell(rs, i+1);
                }

                else if(connectors.at(i) == "#") {
                    Command* l = new Rshell(arguments[i]);
                    l->execute();
                }

                else if(connectors.at(i) == ";"){
                    Command* l = new Rshell(arguments[i-paran]);
                    Command* r = new Rshell(arguments[(i-paran)+1]);
                    Semicolon* semicolonObj = new Semicolon(l, r);
                    semicolonObj->execute();
                }
                else if(connectors.at(i) == "||"){
                    Command* l = new Rshell(arguments[i-paran]);
                    Command* r = new Rshell(arguments[(i-paran)+1]);
                    Or* orObj = new Or(l, r);
                    orObj->execute();
                }
                else if (connectors.at(i) == "[") {
                    struct stat sb;
                    bool exists = false, is_dir = false, is_reg = false;
                    bool status = true;
                    string test_input;

                    // cout << args.at(i) << endl;
                    vector<string> test_args = split_by_space(args.at(i));
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
                        }

                }
            }
                // else if (args.at(i).substr(0, 3) == "test") {
                //     struct stat sb;
                //     cout << "its a test!" << endl;
                // }
            }
        }
    }

}
