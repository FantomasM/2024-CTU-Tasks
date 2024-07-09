CXX=g++
CXXFLAGS=-Wall -pedantic -Wno-long-long -Werror -std=c++17 -z noexecstack 
LD=g++
LDFLAGS=-Wall -pedantic -std=c++17 -Wno-long-long -Werror -z noexecstack 


SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp, %.o, $(SRCS))

Task: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o a.out

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

compile: Task

run: compile
	./a.out

clean:
	rm -f a.out $(OBJS) *~ core
