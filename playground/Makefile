CC = g++
CFLAGS = -Wall -O0 -std=c++11

all: server client

server: server.c
	${CC} ${CFLAGS} -o server server.c

client: client.cc
	${CC} ${CFLAGS} -o client client.c

.PHONY: clean all

clean:
	rm -rf *.o server client