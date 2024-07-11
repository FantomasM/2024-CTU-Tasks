CXX=g++
LD=g++
AR=ar
CXXFLAGS=-std=c++20 -Wall -g -pedantic -O2
SHELL:=/bin/bash
MACHINE=$(shell uname -m)-$(shell echo $$OSTYPE)
SRC_DIR = src

all: test

deps:
	g++ -MM src/*.cpp > Makefile.d

test: task1.o sample_tester.o
	$(LD) $(CXXFLAGS) -o $@ $^ -L./$(MACHINE) -lprogtest_solver -lpthread

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lib: progtest_solver.o bigint.o
	mkdir -p $(MACHINE)
	$(AR) cfr $(MACHINE)/libprogtest_solver.a $^

clean:
	rm -f *.o test *~ core sample.tgz Makefile.d

pack: clean
	rm -f sample.tgz
	tar zcf sample.tgz --exclude progtest_solver.cpp --exclude Makefile.mingw --exclude bigint.cpp *


-include Makefile.d
