# Compile/run:
     - Compile using
            make CalcYouLater
     - run executable with
            ./CalcYouLater [ < test_file.cylc ]

# Program Purpose: 
The purpose of this program is to serve as a RPN, 
or Reverse Polish Notation, Calculator. The user
can input commands in the form of numbers, booleans, 
strings, and operations, and the RPNCalc will process 
and execute accordingly.

Acknowledgements: Lectures, Piazza responses from instructors, 
cplusplus.com references

# Files: 
main.cpp:
     This file holds the main function that creates an instance of
     the calculator and "runs" it, allowing the user to start inputting
     commands and performing operations.

RPNCalc.cpp:
     This file defines the implementation of the RPNCalc class.
     After the run command is called, the program calls upon the private 
     execute_commands helper function to do most of the heavy lifting for
     handling the user's input commands. Within this private function, 
     commands are processed and executed until the quit command is
     called or there is no more input to read from. The execute_commands
     function returns a boolean that indicates whether the program should 
     continue reading input from the next input source or if it should
     quit the calculator completely.

RPNCalc.h:
     The purpose of this file is to define the interface
     of the RPNCalc Class. Public methods include the constructor and the run
     function that kicks off the Calcyoulater (needed by main.cpp)
     Private methods include a DatumStack, which is used to store the 
     values that the user pushes/performs commands on, an execute_commands 
     function that actually accepts input and handles the command being
     asked of the Calcyoulater, and the provided got_int function that
     checks if a string can be interpreted as an integer.

DatumStack.cpp:
     This file defines the implementation of the DatumStack class.
     As a DatumStack is essentially just a linked list of Datum objects,
     it relies mainly on std::list operations to implement its methods.
     DatumStack will throw runtime errors if the client attempts to 
     access or remove the top element of an empty DatumStack.

DatumStack.h:
     Defines the interface for the DatumStack class. Public methods allow
     the client to add to, remove from, and access the top of the stack, as 
     well as clear all of the stack's contents and check its empty/nonempty 
     size. The DatumStack is implemented as a linked list of Datum objects.

unit_tests.h:
     This file holds the unit tests that test the functionality
     and edge cases for the DatumStack class.

parser.cpp:
     Contains the function definition for the parseRString
     function

parser.h:
     Declares the parseRString function, 
     which accepts input of type istream and returns a 
     string in rstring format.

1simple.cyl: Simple commands test. Pushes numbers and booleans onto the
     stack and calls simpler commands with them (not, print, swap, dup, clear,
     etc.)

comparison.cyl: Comparisons tests. Pushes numbers and booleans onto the 
     stack and tests comparison operators with them (>, <, >=, ==, etc.)

copy.cyl: fact.cyl function with added print statements

exec_test.cyl: Tests for exec commands. Tests exec when called on nested
     and non-nested rstrings

file_test.cyl: Tests for file command. Tests file on other cyl testing 
     files, some of which include exec/file commands
     themselves

if_test.cyl: tests if command using a simple test and a test that would    
     require the program to exec a file (meaning both exec and file would be 
     true simulatenously)

nested_if.cyl: test for if command. uses nested if from HW spec

operations.cyl: tests operation commands. pushes numbers onto stack and
     calls opartions on them

strings.cyl: tests that rstrings are properly parsed and pushed onto the stack
     (note: this file serves as a testing file for parse rstring as well)

error.cyl: tests that error messages print according to the reference


# Data Structures:
The Data Structure used in this project was the Stack. The RPNCalc relies 
primarily on the DatumStack, or a stack of Datum elements, that I 
implemented using a linked list. The linked list proved to be most effective
in implementing the stack as it allows the program to add to and access the 
back, or "topmost" element in O(1) access time. Also, since stacks are a last
in, first out data structure, they proved useful for implementing a calculator
that performs reverse polish notation, and "reads" commands in from right to 
left (i.e. the most recently pushed element is the first to be grabbed when
an operation is called). Additionally, stacks are good for task interruption
and resumption; this was especially helpful for the calculator's file and 
exec commands, which stopped accepting commands to go and 
execute the command or file of commands within the topmost rstring, then
resumed accepting input after completing this task. Stacks can be tricky
to implement if you would like random access to a list of data, as the 
worst case would require the program to iterate through the entire stack
before finding the element. However, the stack was perfect for RPNCalc
because it only ever cared about the most recently "pushed on" element.

# Testing:
I started by implementing my DatumStack class, which I tested using unit
testing. I focused mianly on edge cases that I thought would be relevant 
once I implemented the CalcYouLater; pushing on a lot of elements, 
clearing an empty and nonempty stack, making sure the top of the
stack updates as elements are added and removed. I also made sure that the
proper error messages were thrown when illegal commands were called 
(i.e. pop() and top() on an empty stack). Next I moved into implementing 
my parser function, which I tested by making input files containing
strings, then using a main function to pass the strings to the parser via 
the file and cout the output. I was having trouble getting it to read in 
complete nested rstrings, as it was stopping after seeing the first closing 
bracket. I fixed this issue by using int variables to keep track of the number
of open and closing braces, and only ending once these values were the same
(this worked fine, since we were guaranteed that rstrings would always 
be in proper, brace-matching format).

In phase 2, I began implementing the RPN Calc Class. The "simpler" commands
were relatively easy to implement, as they only required a few steps. I
tested them using input files like 1simple.cyl, operations.cyl, and
comparison.cyl, which included a lot of print statements to ensure that
the right values were being pushed onto the stack after each command. 
I input these files to both my CalcYouLater and the reference
implementation and diffed them to ensure that my output was correct. 
I then moved onto the exec and file commands, which gave me some trouble
for a while. I initially considered using global variables
to indicate that the program was executing the command within a file or 
rstring, and not just executing commands provided by cin. When I went
to test this method with the provided factorial function, it didn't work
past the first round of calculations (i.e. when the function was told 
to execute fact.cylc the second time, it was all confused about
which commands it was supposed to execute and which to push onto 
the stack). I then decided that it was best if I just contained 
each "round" of executing commands within its own function call, 
so I fed the filenames and exec commands into a stringstream and
called the execute_commands function with the stream, so that 
it would completely finish executing the argument commands before 
resuming accepting input from cin. I tested that this worked by
creating testing files that had recursive file commands within 
exec commands and vice versa, as well as nested if statements 
that could potentially cause problems. I debugged as I went and
got my output to match the reference, except my function
was not responding the the quit query like it was supposed to;
if it recieved a quit command within a file, it would not
quit the calculator completely, it would just return from the
scope of its given function call. I then decided to change the return
type of the execute_commands function to a boolean, so it would
turn false when it was supposed to quit the calculator completely. 
Once I diffed my program with the reference across all testing files,
I created one last errors.cyl file to ensure that error messages
matched as well. I had to make a few changes small syntax changes
to get them to match up.

# Time Spent
~ 30 hours

