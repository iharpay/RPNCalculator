/* main.cpp
*
* Ayah Harper
* 2/26/23
*
* Purpose: This file holds the main function that creates an instance of
the calculator and "runs" it, allowing the user to start inputting
commands and performing operations.
*
*/
#include "RPNCalc.h"
#include <iostream>

using namespace std;

/* name: main
* purpose: to build and run an instance of the RPNCalc
* arguments: none
* returns: 0
* effects: creates an RPN Calc instance, then calls its
run function to begin the simulation
*/
int main() {

    RPNCalc myCalc;

    myCalc.run();

    return 0;

}
