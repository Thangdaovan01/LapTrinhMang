CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: server client

server: server.c
	${CC} server.c -o server
client: client.c
	${CC} client.c -o client
clean:
	rm -f *.o *~
