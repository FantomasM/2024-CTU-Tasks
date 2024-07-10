CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -I./libs
LD=g++
LDFLAGS=-Wall -pedantic -std=c++17
LOGIN=otamamyk

SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp, %.o, $(SRCS))

Gamebook: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $(LOGIN) -lncurses

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

compile: Gamebook

run: compile
	./$(LOGIN)

clean:
	rm -f $(LOGIN) $(OBJS) *~ core

doc:
	doxygen Doxyfile
