CC=g++
CFLAGS=-Wall  -pedantic -Wno-long-long -Werror
LDFLAGS=-z noexecstack 

SRCS=$(wildcard src/*.c)

a.out: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

compile: a.out

run: compile
	./a.out

clean:
	rm -f a.out
	

.PHONY: compile run clean	
