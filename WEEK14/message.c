#include <stdio.h>
#include <stdlib.h>

#include "message.h"

int receiveMessage(int connfd, Message* message) {
  int ret;
  ret = recv(connfd, message, sizeof(Message), 0);
  if (ret == -1) {
    perror("\nError: ");
    return 0;
  }
  return 1;
}

int sendMessage(int connfd, Message* message) {
  int ret;
  ret = send(connfd, message, sizeof(Message), 0);
  if (ret == -1) {
    perror("\nError: ");
    return 0;
  }
  return 1;
}

