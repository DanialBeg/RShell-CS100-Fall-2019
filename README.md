# CS 100 Programming Project

### Quarter & Year
Fall 2019
### Students
Danial Beg (862070454), dbeg001@ucr.edu\
Zubair Qazi (862076454), zqazi004@ucr.edu

# Introduction
R'Shell is a command shell which will be capable of taking in multiple commands, separated by the connectors `||` , `&&`, or `;`, and executing them in order. Commands have the following format:
```
$ executable [argumentList] [connecter] [executable] ...
```
There can be any number of executables, so long as they are separated by connectors. The execution is dependent on the connectors, as well as the type of connectors, since each has it own unique function. The commands will be represented using the composite pattern, and they will be processed and then executed using the system calls *fork, execvp* and *waitpid*. 

Everytime a syscall is run, it will be checked for an error condition and if an error occurs we will call *perror*. Exit will have its own dedicated command that will exit a specific function while adhering to the connector rules as stated above. The R'Shell will also be able to ignore comments from in-line commands starting with `#`.

# Diagram
![OMT Diagram](/images/Artboard%201@400x-100.jpg)

# Classes
### Input: 
This class parses through user inputs, creating Command objects (along with their arguments) and storing them into a vector of Command objects. Connectors are also parsed and stored into a vector of strings, which will be used in the Connectors class to determine the connector. Parsing is done within a function in the Input class, and the entire input is parsed at once. 
### Command: 
The Command class holds a vector of arguments and contains a pure virtual execute function which must be implemented individually by its children. Each Command object will only hold its respective arguments, parsed up to a connector in the Input parse function.
### Connectors: 
#### And: 
This class is for executing commands and arguments that are linked with the `&&` keyword. The way this will work is by executing a command on the left hand side of the connector, checking if that command executes with no errors, then continuing executing the right side command. If, however, the first command does fail then the execute function will not execute the right hand side as per the assignment guidelines.
#### Or:
This class is for executing commands and arguments that are linked with the `||` keyword. This works similar to "And" above in that this will work is by executing a command on the left hand side of the connector, checking if that command executes with errors, then continuing executing the right side command. If, however, the first command does not fail then the execute function WILL NOT execute the right hand side as per the assignment guidelines, contrary to "And".
#### Semicolon:
This class is for executing commands and arguments that are linked with the `;` keyword. This will work is by executing a command on the left hand side of the connector and then continuing executing the right side command regardless of any error condition.
#### Input Redirect:
This class is for executing input redirects that are linked with the `<` keyword. This works by passing in the right argument into the command, and uses the `dup()` and `dup2()` functions.
#### Output Redirect (`>`):
This class is for executing output redirects that are linked with the `>` keyword. This works by passing in the right argument into the command, and uses the `dup()` and `dup2()` functions. The functionality of this class is to overwrite any data in an existing file. 
#### Output Redirect (`>>`):
This class is for executing output redirects that are linked with the `>>` keyword. This works by passing in the right argument into the command, and uses the `dup()` and `dup2()` functions. The functionality of this class is to append data to an existing file.
#### Piping:
This class is for executing output redirects that are linked with the `|` keyword. This works by passing in the right argument as an additional argument into the command, and uses the `dup()` and `dup2()` functions. The functionality of this class iadd arguments, such as `grep` to another command. 
# Prototypes/Research
### Fork:
```c++
void forkPractice(){
  //Forking creates 2^n processes
  fork();
  fork();
  fork();
  cout << "Hello world!" << endl;
}
```
From as we can see above, fork creates 2^n processes and will run certain code 2^n times. So from the example above, "Hello World!" would be printed 8 times. 
### Execvp:
```c++
void executeTest(){
  char* command = "ls";
  char* args[3];
  args[0] = "ls";
  args[1] = "-la";
  args[2] = NULL;
  execvp(command, args);
}
```
execvp() takes in a character pointer as well as a character array and will execute the bash command from the character pointer with the flags from the character array. An important thing to note is that the last element in the argument list MUST be Null.

### Waitpid:
```c++
void waitExample(){
  pid_t pid = fork();
  int stat;

  if(pid == 0){
    executeTest();
  }
  waitpid(pid, &stat, 0);
}
```
waitpid() takes in a pid status which could be less than -1 (wait for a child process whose ID is equal to abs(pid)), -1 (wait for child process), 0 (wait for child process where the id is the same as what called it), or greater than 1 where it waits for a child process whose id is the same as pid. waitpid() essentially stops execution of a process (for example created by fork) until a child has changed its status.

# Development and Testing Roadmap
1. Implement Command class [#1](https://github.com/cs100/assignment-legostarwarsguys/issues/1)
    1. Create ls function
    1. Create echo function
    1. Create mkdir function
1. Implement Input class [#2](https://github.com/cs100/assignment-legostarwarsguys/issues/2)
    1. Design and create parser function
1. Unit test parser function [#3](https://github.com/cs100/assignment-legostarwarsguys/issues/3)
1. Implement Exit class [#4](https://github.com/cs100/assignment-legostarwarsguys/issues/4)
    1. Implement unique exit function
1. Implement Connector class [#5](https://github.com/cs100/assignment-legostarwarsguys/issues/5)
    1. Design AND and its unique execute function
    1. Design OR and its unique execute function
    1. Design SEMICOLON and its unique execute function
1. Unit Test AND, OR, SEMICOLON execute function [#6](https://github.com/cs100/assignment-legostarwarsguys/issues/6)
1. Perform Integration test with Command in Connector class [#7](https://github.com/cs100/assignment-legostarwarsguys/issues/7)
1. Unit Test Exit class and its functionality [#8](https://github.com/cs100/assignment-legostarwarsguys/issues/8)


# Assignment 2 Updates
We realized we didn't need the exit class as we could just call that from execvp() in Rshell.cpp. We took a few classes out and decided to add some different ones. For example, we added an Rshell class which would be the leaf node and do all the execution for our objects. 

We also removed our Input class as that caused a lot of errors and instead added those functions in our `main.cpp` instead. We are now able to run all bash commands from our command-line.

# Assignment 3 Updates
The overall structure of our program did not change (regarding our file and folder locations). We added test files in the integration_tests and unit_tests folders in order to test the functionality of test and precedence. We were able to implement both precedence and tests without adding new classes/files to our program. The specific changes in each area of our project are as follows:
* Parsing
  * Minimal changes were made to our method of parsing for this assignment, since we did not have to change the functionality of the parser. The only necessary changes were to account for `[` and `]`. We did not check for `test` in our parser because it was unnecessary to implement due to the structure and functionality of our program.
* R'shell
  * R'shell had to be changed in order to account for parentheses and square brackets in user input. While no structural changes had to be made in order to implement precedence and testing, a good amount of checking certain conditions, including edge cases, was required. Our implementation of test was placed in the execute function of R'shell, and checks were made before execution in order to decide which execute to run (test function or original execute). These checks specifically looked for `[`, `]`, and `test` within the user input.
* Testing
  * Unit Testing
    * As per the assignment requirements, we implemented unit tests for precedence and testing. We utilized some of the examples in the assignment document, as well as a few more complicated examples of our own, in order to ensure the functionality of our program.
  * Integration Testing
    * As per the assignment requirements, we added three integration test scripts: `test_literal_tests.sh`, `test_symbolic_tests.sh`, and `precedence_tests.sh`. Each test checks for specific implementations of test or precedence. We also added test cases designed to fail, in order to ensure that precedence and tests were functioning as required. 

We also came across some issues when completing this assignment. Each issue was mostly resolved individually, as they are checked within the unit and integration tests. They are as follows:
* Implementing precedence
  * We initially had issues implementing precedence because they were not functioning correctly with single commands and with connectors between parenthesis. This was eventually resolved by keeping track of the parentheses during execution. 
* Using the `stat()` function
  * There were initially issues using the `stat()` function  for testing because we did not understand the implementation and use of the macros. However, this was easily resolved by reading into the documentation for stat() provided in the assignment document. 
* Combining tests with previous functions
  * Originally, after the initial implementation, our test function using stat() did not work properly with connectors, and by relation precedence. This was resolved by moving our code from its original location in a test file to R'shell, within the execute function, and checking for the `test` keyword or symbols `[` and `]` before calling execute (the appropriate implementation of test or execute).

# Assignment 4 Updates
For this assignment we had to add new connectors, specifically `<`, `>`, `>>`, and `|` to our program. This did not fundamentally change our program structure because we simply needed to add these connectors alongside the connectors, and implement the `execute()` function accordingly. The specific changes in each area of our program is as follows:
* Parsing
  * Once again, minimal changes were made to our method of parsing for this assignment, since we did not have to change the functionality of the parser. The only necessary changes were to account for `<`, `>`, `>>`, and `|`. We did not need to implement any extra checks.
* R'shell
  * R'shell had to be changed in order to account for the redirects and pipes in user input. While no structural changes had to be made in order to implement redirection and piping, a good amount of checking certain conditions, including edge cases, was required. We simply had to implement the functionality in separate `execute()` functions in each class, and no changes were required beyond this.
* Piping
  * A separate class for piping was required, in order to implement the `execute()` function for it separately. We were required to use a variety of syscalls, such as `pipe`, `dup()`, and `dup2()`, in order to implement the functionality. Pipes (`|`) were treated as connectors within R'shell.
* Input Redirect
  * A separate class for input redirection was reqiured, in order to implement the `execute()` function separately. `dup()` and `dup2()` were once again required for implementation. Input redirects (`<`) were once again treated as connectors in R'shell.
* Output Redirects
  * Two separate class for output redirection was reqiured, one for `>` and another for `>>`, in order to implement the `execute()` function separately. `dup()` and `dup2()` were once again required for implementation. Output redirects (`>` and `>>`) were once again treated as connectors in R'shell.
* Testing
  * Unit Testing
    * As per the assignment requirements, we implemented unit tests for redirects and piping. We utilized some of the examples in the assignment document, as well as a few more complicated examples of our own, in order to ensure the functionality of our program.
  * Integration Testing
    * As per the assignment requirements, we added three integration test scripts: `input_redirection_tests.sh`, `output_redirection_tests.sh`, and `pipe_operator_tests.sh`. Each test checks for specific implementations of redirection or piping.
    
We also came across some issues when completing this assignment. Each issue was mostly resolved individually, as they are checked within the unit and integration tests. They are as follows:
* Implementing redirection
  * We initially had issues implementing redirection because we were unsure of the functionality of `dup()` and `dup2()`. This was solved by reading the man page extensively, and finding examples for each.
