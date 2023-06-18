###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Ayah Harper

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) $(LDFLAGS) main.o RPNCalc.o DatumStack.o Datum.o parser.o -o CalcYouLater

main.o: main.cpp RPNCalc.o
	$(CXX) $(CXXFLAGS) -c main.cpp
	
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.o parser.o
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

parser.o: parser.cpp parser.h 
	$(CXX) $(CXXFLAGS) -c parser.cpp

DatumStack.o: DatumStack.cpp DatumStack.h Datum.o
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp


unit_test: unit_test_driver.o DatumStack.o Datum.o parser.o
	$(CXX) unit_test_driver.o DatumStack.o Datum.o parser.o

Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

%.cylc:  %.cyl
	./cylc $^
