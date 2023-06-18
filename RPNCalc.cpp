/* RPNCalc.cpp
*
* Ayah Harper
* 2/26/23
*
* Purpose: This file defines the implementation of the RPNCalc class.
     After the run command is called, the program calls upon the private 
     execute_commands helper function to do most of the heavy lifting for
     handling the user's input commands. Within this private function, 
     commands are processed and executed until the quit command is
     called or there is no more input to read from. The execute_commands
     function returns a boolean that indicates whether the program should 
     continue reading input from the next input source or if it should
     quit the calculator completely.
*
*/

#include "RPNCalc.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>

using namespace std;

/* name: default constructor
* purpose: initialize an RPNCalc object
* arguments: none
* returns: none
* effects: none
*/
RPNCalc::RPNCalc() {
}

/* name: run
* purpose: public wrapper function for running commands
* arguments: none
* returns: none
* effects: calls the execute_commands function with input
type cin, sends goodbye message when complete
*/
void RPNCalc::run() {
    
    execute_commands(cin);

    cerr << "Thank you for using CalcYouLater." << endl;

}

/* name: execute_commands
* purpose: private helper function for handling commands
* arguments: input of type istream
* returns: boolean
* effects: processes the input and executes
the corresponding command. returns true if there is still
more input to accept (i.e. it has only reached the end of CURRENT
input source, does not want to quit the calculartor completely) 
and false if an input source has requested to quit the calculator 
entirely.
*/
bool RPNCalc::execute_commands(istream &input) {

    string command;

    while (input >> command and command != "quit") {
    try {
        int num;
        if (got_int(command, &num)) {
            Datum numb(num);
            theStack.push(numb);
            
        } else if (command == "#t" or command == "#f") {
            if (command == "#t") {
                Datum truth(true);
                theStack.push(truth);
            } else if (command == "#f") {
                Datum lie(false);
                theStack.push(lie);
            } 

        } else if (command == "not") {
                bool next = false;
                next = !theStack.top().getBool();
                Datum opp(next);
                theStack.push(opp);

        } else if (command == "print") {
            if (theStack.isEmpty()) {
                cerr << "Error: empty_stack" << endl;
            } else {
                cout << theStack.top().toString() << endl;
            }
        } else if(command == "clear") {
            theStack.clear();

        } else if(command == "drop") {
            theStack.pop();

        } else if (command == "dup") {
            Datum dupe(theStack.top());
            theStack.push(dupe);

        } else if (command == "swap") {
            // pop the top two values off the stack
            Datum first(theStack.top());
            theStack.pop();
            Datum second(theStack.top());
            theStack.pop();

            // push them back onto the stack in reverse order
            theStack.push(first);
            theStack.push(second);

        } else if (command == "+" or command == "-" or command == "*" or 
                   command == "/" or command == "mod") 
        {
            // pop the top two values off the stack
            Datum deep(theStack.top());
            theStack.pop();
            Datum deeper(theStack.top());
            theStack.pop();

            int value = -1;

            // perform the operation on the two values
            if (command == "+") {
                value = deeper.getInt() + deep.getInt();
            } else if (command == "-") {
                value = deeper.getInt() - deep.getInt();
            } else if (command == "*") {
                value = deeper.getInt() * deep.getInt();
            } else if (command == "/") {
                value = deeper.getInt() / deep.getInt();
            } else if (command == "mod") {
                value = deeper.getInt() % deep.getInt();
            }
        
            // push the result onto the stack
            Datum result(value);
            theStack.push(result);
 
        } else if (command == "<" or command == ">" or command == "<=" or 
                   command == ">=" or command == "==")
        { 
            // pop the top two values off the stack
            Datum deep(theStack.top());
            theStack.pop();
            Datum deeper(theStack.top());
            theStack.pop();

            bool loobean = false;

            // compare the values
            if (command == "<") {
                loobean = deeper.getInt() < deep.getInt();
            } else if (command == ">") {
                loobean = deeper.getInt() > deep.getInt();
            } else if (command == "<=") {
                loobean = deeper.getInt() <= deep.getInt();
            } else if (command == ">=") {
                loobean = deeper.getInt() >= deep.getInt();
            } else if (command == "==") {
                if (deep.isBool() and deeper.isBool()) {
                    loobean = deeper.getBool() == deep.getBool();
                } else {
                    loobean = deeper.getInt() == deep.getInt();
                }
            }
            
            // push the result onto the stack
            Datum result(loobean);
            theStack.push(result);
         
        } else if (command == "{") {
            string rString;
            rString = parseRString(input);
            Datum ourString(rString);
            theStack.push(ourString);
            

        } else if (command == "}") {
            continue;

        } else if (command == "exec") {
            stringstream exs;
            string trash;

            if (!theStack.top().isRString()) {
                cerr << "Error: cannot execute non rstring\n";
            } else {
                // pop the rstring to be exec'd off the stack
                exs << theStack.top().getRString();
                theStack.pop();
                // get rid of the opening brace and execute the
                // contents of the rstring
                exs >> trash;
                if (not execute_commands(exs)) {
                    return false;
                }
            }

        } else if (command == "file") {
            stringstream fs;
            string trash, filename;

            if (!theStack.top().isRString()) {
                cerr << "Error: file operand not rstring\n";
            } else {
                // pop the file rstring off the stack
                fs << theStack.top().getRString();
                theStack.pop();
                // extract just the filename
                fs >> trash >> filename >> trash;
                // attempt to open file, return the result of 
                // executing the commands within the file
                ifstream infile;
                infile.open(filename);
                if (not infile.is_open()) {
                    cerr << "Unable to read " << filename << endl;
                } else {
                    if (not execute_commands(infile)) {
                        return false;
                    }
                }
            }

        } else if (command == "if") {

            stringstream ifs;
            string trash;

            // pop the false case, true case, and 
            // test condition off the stack
            Datum falseCase(theStack.top());
            theStack.pop();
            Datum trueCase(theStack.top());
            theStack.pop();
            Datum testCondition(theStack.top());
            theStack.pop();

            // check to be sure they have the proper parameters
            if (!testCondition.isBool()) {
                cerr << "Error: expected boolean in if test\n";
                continue;
            }
            if (!falseCase.isRString() or !trueCase.isRString()) {
                cerr << "Error: expected rstring in if branch\n";
                continue;
            }

            // execute false case if boolean is false
            // execute true case if boolean is true
            if (!testCondition.getBool()) {
                ifs << falseCase.getRString();
                ifs >> trash;

            } else {
                ifs << trueCase.getRString();
                ifs >> trash;
            } 

            if (not execute_commands(ifs)) {
                return false;
            }

        } else {
            cerr << command << ": unimplemented" << endl;
        }

    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    }

    continue;

}
    if (command == "quit") {
        return false;
    }

    return true;
    
}

/* name: got_int 
* purpose: determines if a string can be interpreted as an integer
* arguments: a string, a pointer to the integer variable to store the 
result at if it can be processed as a string
* returns: boolean indicating if the result can be interpreted as an integer
* effects: uses sscanf function to determine if the argument string can
be interpreted as an integer. If true, stores the integer in the 
*/
bool RPNCalc:: got_int(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;

}
