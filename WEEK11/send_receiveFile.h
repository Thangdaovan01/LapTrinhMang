#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#define BUFF_SIZE 1024

typedef struct{
	int opcode;
	int length;
	char payload[BUFF_SIZE];
} Message;

int receiveMessage(int connfd, Message* message) {
    int ret;
    ret = recv(connfd, message, sizeof(Message), 0);
    if (ret == -1) {
     perror("\nError: ");
    }
    return ret;
}

int sendMessage(int connfd, Message* message) {
    int ret;
    ret = send(connfd, message, sizeof(Message), 0);
    if (ret == -1) {
        perror("\nError: ");
    }
  return ret;
}

void receiveFile(int connfd, FILE* output) {
    Message message;

    while (1) {
        if (!receiveMessage(connfd, &message)) {
            break;
        }
        if (message.opcode != 3) {
            break;
        }
        if (message.length == 0) {
            break;
        }
        fwrite(message.payload, sizeof(char), message.length, output);
    }
}

void sendFile(int connfd, FILE* input) {
    Message message;
    int n;
    message.opcode = 3;

    while (1) {
        n = fread(message.payload, sizeof(char), BUFF_SIZE - 1, input);
        if (n == 0) {
            break;
        }
        message.length = n;
        if (!sendMessage(connfd, &message)) {
            break;
        }
    }

    message.length = 0;
    if (!sendMessage(connfd, &message)) {
        return;
    }
}