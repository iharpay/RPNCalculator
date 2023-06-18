/* DatumStack.h
* 
* Ayah Harper
* 2/23/2023
*
* Purpose: Defines the interface for the DatumStack class. Public methods allow
the client to add to, remove from, and access the top of the stack, as well as 
clear all of the stack's contents and check its empty/nonempty size. The 
DatumStack is implemented as a linked list of Datum objects.
*
*/

#ifndef _DATUMSTACK_
#define _DATUMSTACK_

#include "Datum.h"
#include <list>

class DatumStack {
public:
    //Constructors
    DatumStack();
    DatumStack(Datum data[], int size);

    ~DatumStack();

    bool isEmpty();
    int size();
    void clear();
    Datum top();
    void pop();
    void push(Datum data);
private:
    std::list<Datum> myStack;

};

#endif
