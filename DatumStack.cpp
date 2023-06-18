/* DatumStack.cpp
*
* Ayah Harper
* 2/23/2023
* 
* Purpose: This file defines the implementation of the DatumStack class.
As a DatumStack is essentially just a linked list of Datum objects,
it relies mainly on std::list operations to implement its methods.
DatumStack will throw runtime errors if the client attempts to 
access or remove the top element of an empty DatumStack.
*
*/

#include "DatumStack.h"
#include <stdexcept>

using namespace std;

/* name: default constructor
purpose: intialize an empty DatumStack
arguments: none
returns: none
effects: ensures that the "stack" list is empty, and the 
front and back pointers point to the nullptr
*/
DatumStack::DatumStack(){
}

/* name: specialized constructor
purpose: intiialize a stack with an array of Datum
arguments: a Datum array, an integer indicating the size
of the array
returns: none
effects: pushes the argument elements onto the Stack in order
and recycles the argument array
*/
DatumStack::DatumStack(Datum data[], int size) {

    for (int i = 0; i < size; i++) {
        myStack.push_back(data[i]);
    }

}

/* name: destructor
purpose: recycles all heap allocated 
arguments: none
returns: none
effects: erases all Datum elements in the stack
*/
DatumStack::~DatumStack() {
}

/* name: isEmpty
purpose: determines if the given DatumStack is empty
arguments: none
returns: boolean indicating whether the stack is empty
effects: returns result of std::list empty operation
*/
bool DatumStack::isEmpty() {

    return myStack.empty();

}

/* name: clear
purpose: makes the current stack into an empty stack
arguments: none
returns: none
effects: uses std::list clear operation to clear the stack
*/
void DatumStack::clear() {

    myStack.clear();

}


/* name: size
purpose: get the number of Datum elements in the stack
arguments: none
returns: integer indicating size of the stack
effects: returns result of std::list size operation 
*/
int DatumStack::size() {

    return myStack.size();
}

/* name: top
purpose: get the top Datum element in the stack
arguments: none
returns: the top Datum element in the stack 
effects: returns, but does not remove, the Datum element 
pointed to by the back pointer (back of the list = top of 
the stack). throws runtime error if stack is empty
*/
Datum DatumStack::top() {

    if (myStack.empty()) {
        throw std::runtime_error("empty_stack");
    }
    return myStack.back();
}

/* name: pop
purpose: removes the Datum element on top of the stack
arguments: none
returns: none
effects: removes, but does not return, the Datum element
on top of the stack using std::list pop_back func. throws 
runtime error if the stack is empty
*/
void DatumStack::pop() {

    if (myStack.empty()) {
        throw std::runtime_error("empty_stack");
    }
    
    myStack.pop_back();
}

/* name: push
purpose: pushes the argument Datum element onto the top of the stack
arguments: Datum element to be pushed
returns: none
effects: uses std::list push_back operation to add the Datum element
to the top of the stack
*/
void DatumStack::push(Datum data) {

    myStack.push_back(data);
}


