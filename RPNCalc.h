/* RPNCalc.h
* 
* Ayah Harper
* 2/26/2023
* 
* Purpose: The purpose of this file is to define the interface
of the RPNCalc Class. Public methods include the constructor/
destructor and the run function that kicks off the Calcyoulater.
Private components include a DatumStack, which is used to store the 
values that the user pushes/performs commands on, an execute_commands 
function that actually accepts input and handles the command being
asked of the Calcyoulater, and the provided got_int function that
checks if a string can be interpreted as an integer.
*
*/

#ifndef _RPNCALC_
#define _RPNCALC_

#include "DatumStack.h"
#include <string>
#include <iostream>

using namespace std;

class RPNCalc {
public:
    RPNCalc();
    void run();
private:
    DatumStack theStack;
    bool execute_commands(istream &input);
    bool got_int(string s, int *resultp);
};

#endif
