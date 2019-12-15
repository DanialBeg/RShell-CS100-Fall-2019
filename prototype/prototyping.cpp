#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void forkPractice(){
  //Forking creates 2^n processes
  fork();
  fork();
  fork();
  cout << "Hello world!" << endl;
}

vector<string> parsePractice(string input) {
  string parse = "";
  vector<string> command_args;
  vector<char> connectors;
  for (int i = 0; i < input.size(); i++) {
    if (input.at(i) != '&' || input.at(i) != '|' || input.at(i) != ';')
      parse += input.at(i);
    else {
      connectors.push_back(input.at(i));
      command_args.push_back(parse);
      parse = "";
    }
  }
  return command_args;
}

void executeTest(){
  char* command = "ls";
  char* args[3];
  args[0] = "ls";
  args[1] = "-la";
  args[2] = NULL;
  execvp(command, args);
}

void waitExample(){
  pid_t pid = fork();
  int stat;

  if(pid == 0){
    executeTest();
  }
  waitpid(pid, &stat, 0);
}

int main(){
  string input = "echo arg.cpp ; ls -la";
  vector<string> commands = parsePractice(input);

  for (int i = 0; i < commands.size(); i++) {
    cout << commands.at(i);
  }
  
  forkPractice();
  waitExample();
  executeTest();

  return 0;
}
