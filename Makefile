CC=clang

CFLAGS += -fcolor-diagnostics
CFLAGS += -O3 -Wall
CFLAGS += -ggdb

all: logger

test: test/udp2stdout

clean:
	rm -f *.o test/*.o
	rm -f logger test/udp2stdout
