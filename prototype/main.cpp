#include <iostream>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;
using namespace boost;

vector<int> get_test_indices(vector<string> args) {
    vector<int> ret;

    for (int i = 0; i < args.size(); i++) {
        if (args.at(i).size() > 3) {
            if (args.at(i).substr(0, 4) == "test") {
                ret.push_back(i);
            }
        }
    }
    return ret;
}

string trim_input(string input) {
    string split;

    escaped_list_separator<char> els2("", "\"",  " ");
    boost::tokenizer<escaped_list_separator<char> > tok2(input, els2);

    for(boost::tokenizer<escaped_list_separator<char> >::iterator beg = tok2.begin();
        beg != tok2.end(); beg++) {
        string tmp(*beg);
        split += (tmp);
    }

    cout << "TRIMMED STRING" << endl;
    cout << split << endl;
    cout << "------------------------------------"<< endl;

    return split;
}

// char* string_to_char_arr(string input) {
//    char *c = new char(input.size() + 1);
//    strcpy(c, input.c_str());
//
//    return c;
// }

vector<string> get_connectors(string input) {

    string split = "";

    split = input;
    cout << split << endl;

    string token = "", connector = "";
    vector<string> vect_tokens;

    for (int i = 0; i < split.length(); i++) {

      char c = split[i];
      if (c == '#') {
          // if (token != "")
          //     vect_tokens.push_back(token);
          // token = "";
          connector += c;
          vect_tokens.push_back(connector);
          connector = "";
          break;
      }
      else if (c == '\"') {
          i++;
          // in_quotes = true;
          while (split[i] != '\"') {
            i++;
          }
          // token += c;
      }
      else if (c == '(' || c == ')') {
          connector += c;
          vect_tokens.push_back(connector);
          connector = "";
          // connector += c;
          // vect_tokens.push_back(connector);
          // connector = "";
          // token += c;
      }
      else if (c == '[' || c == ']') {
          connector += c;
          vect_tokens.push_back(connector);
          connector = "";
          // connector += c;
          // vect_tokens.push_back(connector);
          // connector = "";
          // token += c;
      }
      else if (c == ';') {
        connector += c;
        vect_tokens.push_back(connector);
        // this->linkers.push_back(connector);
        connector = "";
      }
      else if (c == '<') {
        connector += c;
        vect_tokens.push_back(connector);
        // this->linkers.push_back(connector);
        connector = "";
      }
      else if (c == '&') {
        connector += c;
        if (split[i + 1] == '&' ) {
          connector += c;
          i++;
        }
        vect_tokens.push_back(connector);
        // this->linkers.push_back(connector);
        connector = "";
        // vect_tokens.push_back("@");
      }
      else if (c == '|') {
        connector += c;
        if (split[i + 1] == '|' ) {
          connector += c;
          i++;
        }
        vect_tokens.push_back(connector);
        // this->linkers.push_back(connector);
        connector = "";
        // vect_tokens.push_back("@");
      }
      else if (c == '>') {
        connector += c;
        if (split[i + 1] == '>' ) {
          connector += c;
          i++;
        }
        vect_tokens.push_back(connector);
        // this->linkers.push_back(connector);
        connector = "";
        // vect_tokens.push_back("@");
      }
      // else {
      //     token += c;
      // }
    }
    return vect_tokens;
}


int main() {

    string user_input;
    vector<string> vect;

    // std::cout << "Enter commands: " << std::endl;
    // getline(std::cin, user_input);
    // std::cout << user_input << std::endl;

    typedef tokenizer<char_separator<char> > tokenizer;

    // string s = "echo \"args args ; \"he\"l\"lo;\" args\"; ls -la | mkdir bin/";
    // string s = "(echo \"hello && ()goodbye;\" || echo \"hello\") || (echo \"hello\" && mkdir trash/)";
    // string s = "echo \"hello world && || ;\"; echo eat food! && ls -la; touch filename || mkdir bin/ ";
    // string s = "echo \"I \"li\"ke; pizza\" && mkdir pizza/; ls -la; touch filename && rm filename;";
    // string s = "echo \"hello\" | echo \"bye\" # or not";
    // string s = "(echo hello && echo \"bye&&\") || (echo no || echo bye)";
    // string s = "(echo hello)";
    // string s = "[-e test/filename/path]";
    // string s = "test -e test/path && echo hello";
    string s = "cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z >> newOutputFile2";
    // string s = "echo Hello < test.txt";

    // string separator1("");//dont let quoted arguments escape themselves
    // string separator2(";");//split on spaces
    // string separator3("\"\'");//let it have quoted arguments

    // boost::replace_all(s, "&&", " & ");
    // boost::replace_all(s, "||", "|");

    cout << "ORIGINAL STRING" << endl;
    cout << s << endl;
    cout << "------------------------------------"<< endl;

    string split = trim_input(s);
    vector<string> connectors = get_connectors(split);
    cout << "CONNECTOR VECTOR" << endl;
    for (auto str : connectors)
        cout << str  << endl;
    cout << connectors.size() << endl;
    cout << "------------------------------------"<< endl;

    // boost::replace_all(split, "\"", " \"");
    // boost::replace_all(split, ";", " ;");
    // boost::replace_all(split, "&", " &");
    // boost::replace_all(split, "|", " |");

    escaped_list_separator<char> els("", "&&||;#()[]<>",  "\"\"");
    boost::tokenizer<escaped_list_separator<char> > tok(s, els);

    cout << "COMMAND VECTOR" << endl;
    for(boost::tokenizer<escaped_list_separator<char> >::iterator beg = tok.begin();
        beg != tok.end(); ++beg) {

        string tmp(*beg);

        boost::trim(tmp);
        if (!tmp.empty()) {
            vect.push_back(tmp);
            cout << "<" << tmp << ">" << endl;
        }
    }
    cout << vect.size() << endl;
    cout << "------------------------------------"<< endl;

    // for (int i = 0; i < vect.size(); i++) {
    //     if (vect.at(i) == "") {
    //         erase
    //     }
    // }


    //const_cast<char*> learned from class-mate Hugo Contreras
    char** ch = new char*[vect.size()];
    for (int i = 0; i < vect.size(); i++) {
        ch[i] = const_cast<char*>(vect.at(i).c_str());
    }
    // for(int i = 0; i < chars.size(); ++i) {
    //     ch[i] = new char[strlen(chars.at(i))];
    //     ch[i] = chars.at(i);
    // }

    cout << "CHARACTER ARRAY" << endl;

    for (int i = 0; i < vect.size(); i++) {
        cout << ch[i] << endl;
    }

    cout << "------------------------------------"<< endl;

    cout << "NUMBER OF \'test\' LITERALS" << endl;

    vector<int> ind = get_test_indices(vect);
    cout << "INDICES SIZE: " << ind.size() << endl;

    // for (int i = 0; i < vect.size(); i++) {
    //     delete[] ch[i];
    // }
    delete[] ch;

}
