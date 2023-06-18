/* parser.cpp
*
* Ayah Harper
* 2/24/2023
*
* Purpose: This file contains the implementation of the
parseRString function. This parser is useful for parsing
through input streams and returning strings in 
proper rstring ( { content } ) format for the RPNCalc.
*
*/

#include "parser.h"

using namespace std;

/* name: parseRString
* purpose: parse through input to return an rstring 
* arguments: input of type istream
* returns: a string in rstring format
* effects: goes through the input stream, adding each string
bit it picks up to an rString until either all braces
have been matched or it reaches the end of the input
*/
std::string parseRString(std::istream &input) {

    string rString;
    string next;

    int open = 1;
    int close = 0;

    while (!input.eof() and open != close) {
        input >> next;

        if (next == "{") {
            open++;
        }
        if (next == "}") {
            close++;
        }

        rString += " " + next;
    }

    return "{" + rString;
 

}

