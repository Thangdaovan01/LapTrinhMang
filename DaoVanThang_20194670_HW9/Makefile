CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: server client

server: server.c
	${CC} server.c -o server -pthread
client: client.c
	${CC} client.c -o client -pthread
clean:
	rm -f *.o *~
