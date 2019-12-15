#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Input {
    private:
        // // Private members
        // char** commandList;
        // vector<string> connectors;

        // Helper Function
        string trim_input(string );
        //string in;

    public:
        Input(){};
        vector<string> parse_input(string );
        vector<string> get_connectors(string );
};

#endif //__INPUT_HPP__
