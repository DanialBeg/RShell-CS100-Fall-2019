#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "input.hpp"

using namespace std;
using namespace boost;

//FUNCTION: Public parse function which populates commandList and connectors
vector<string> Input::parse_input(string input) {
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
            // cout << "<"<< tmp << ">" << endl;
        }
    }

    return vect;
}

//FUNCTION: trims input of spaces and extra quotes to count connectors
string Input::trim_input(string input) {
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
vector<string> Input::get_connectors(string input) {

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
