#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


typedef struct sockaddr_in SOCK_ADDR;
const int BUFF_SIZE = 1000;


int checkBuff(char *str){
    for (int i = 0; str[i] != 0; i++){
        if (str[0] && strlen(str) == 1)return 1;
        if (str[i] < '0'
        || (str[i] > '9' && str[i] < 'A')
        || (str[i] > 'Z' && str[i] < 'a')
        || str[i] > 'z')return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){

//    if (argc < 3){
//        printf("fail to param!");
//        return 0;
//    }
//    char *ip = argv[1];
//    int port = atoi(argv[2]);
    char enter;
    char ip[] = "127.0.0.1";
    int port = 5555;
    int rcvBytes = -1, sendBytes;
    int len;
    SOCK_ADDR servaddr;
    int sockfd;
    char buff[BUFF_SIZE+1];
    memset(buff, 0, sizeof(buff));
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Error: ");
        return 0;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);
    buff[0] = '*';
    len = sizeof(servaddr);
    sendBytes = sendto(sockfd, buff, strlen(buff), 0,(struct sockaddr *) &servaddr, len);


    while(1){
        if (rcvBytes == -1){
            printf("\n\tGõ \"continue#\" rồi nhấn enter để bỏ qua:\n\tHoặc nhập xâu:\n");
            scanf("%s", buff);
            scanf("%c", &enter);
            if (!strcmp(buff, "continue#")){
                rcvBytes = 0;
                continue;
            }
            if (!checkBuff(buff)){
                printf("\n\tError!\n");
                continue;
            }
        }else
        if (rcvBytes > 0){
            printf("%s", buff);
            rcvBytes = -1;
            continue;
        }

        len = sizeof(servaddr);
        if (rcvBytes == -1)sendBytes = sendto(sockfd, buff, strlen(buff), 0,(struct sockaddr *) &servaddr, len);
        if(sendBytes < 0){
            perror("Error: SEND");
            return 0;
        }
        if (!strcmp(buff, "") || !strncmp(buff, "exit", 4))break;
        rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0,(struct sockaddr *) &servaddr, &len);
        buff[rcvBytes] = '\0';
        if (!strncmp(buff, "exit", 4))break;
    }
    close(sockfd);
}