#ifndef _MESSSAGE_H_
#define _MESSSAGE_H_

#define BUFF_SIZE 1024

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

/**
 * @brief Message structure
 * Opcode: 1 byte (0: ENCRYPT_CAESAR, 1: DECRYPT_CAESAR, 2: SEND_FILE, 3: ERROR)
 * Length: 2 bytes
 * Data: n bytes
 */
typedef struct message {
  char *number;
  char *str1;
} Message;

int receiveMessage(int connfd, Message* message);
int sendMessage(int connfd, Message* message);
#endif
