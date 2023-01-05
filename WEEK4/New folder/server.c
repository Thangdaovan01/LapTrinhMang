#include <netinet/in.h>
#include <malloc.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

typedef struct sockaddr_in SOCK_ADDR;
const int BUFF_SIZE = 1000;
typedef struct socket_address{
    SOCK_ADDR elm;
    struct socket_address *next;
}*clientaddr;
int isEmpty(clientaddr root){
    return root->next ? 0 : 1;
}
clientaddr create(){
    clientaddr client = (clientaddr)malloc(sizeof(struct socket_address));
    client->next = NULL;
    return client;
}
clientaddr add(clientaddr tail, SOCK_ADDR cle){
    clientaddr client = create();
    strcpy(client->elm.sin_zero, cle.sin_zero);
    client->elm.sin_addr = cle.sin_addr;
    client->elm.sin_port = cle.sin_port;
    client->elm.sin_family = cle.sin_family;
    tail->next = client;
    return client;
}
void close_all(clientaddr root){
    clientaddr p = root;
    while(p != NULL){
        root = root->next;
        free(p);
        p = root;
    }
}
void close_elm(clientaddr root, clientaddr elm){
    clientaddr p = root;
    if (p == elm){
        root = root->next;
    }
    else{
        while(p->next != elm)p = p->next;
        if (elm->next == NULL)p->next = NULL;
        else
            p->next = elm->next;
    }
    free(elm);
}
clientaddr search(clientaddr root, SOCK_ADDR elm){
    clientaddr p = root->next;
    if (isEmpty(root)){
        return NULL;
    }
    while(p){
        if (p->elm.sin_port == elm.sin_port){
            return p;
        }
        p = p->next;
    }
    return NULL;
}
void xuli(char *buff){
    char strNumber[BUFF_SIZE];
    char strWord[BUFF_SIZE];
    int j = 0, k = 0;
    for (int i = 0; buff[i] != 0; i++){
        if (buff[i] > '0' && buff[i] < '9'){
            strNumber[j++] = buff[i];
        }else{
            strWord[k++] = buff[i];
        }
    }
    strNumber[j] = '\n';
    strcpy(buff, strNumber);
    strcat(buff, strWord);
}
int main(int argc, char *argv[]){
//    if (argc < 2){
//        printf("Failed to param");
//        exit(0);
//    }
//  int port = atoi(argv[1]);
    int port = 5555;
    SOCK_ADDR servaddr, client;
    clientaddr clients = create();
    clientaddr tail = clients;
    int sockfd;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Error: ");
        return 0;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))){
        perror("Error: ");
        return 0;
    }
    printf("server started");
    int len;
    int rcvBytes, sendBytes;
    char buff[BUFF_SIZE+1];
    char success_msg[] = "Successful";
    while(1){
        memset(buff, 0, sizeof (buff));
        len = sizeof (client);
        rcvBytes = recvfrom(sockfd, buff, BUFF_SIZE, 0,(struct sockaddr *) &client, &len);
        buff[rcvBytes] = '\0';
        if (rcvBytes < 0){
            perror("Error: ");
            return 0;
        }else
        if (rcvBytes == 1 && buff[0] == '*'){
            if (search(clients, client) == NULL)tail = add(tail, client);
        }else
        if (strncmp(buff, "exit", 4) == 0){
            // giai phong
            clientaddr p = search(clients, client);
            memset(buff, 0, sizeof(buff));
            strcpy(buff, "exit");
            sendBytes = sendto(sockfd, buff, sizeof (buff), 0, (struct sockaddr *) &(p->elm), len);
            close_elm(clients, p);
            break;
        }else
        if (buff[0] == '\0'){
            strcpy(buff, "exit");
            for (clientaddr p = clients->next; p != NULL; p = p->next){
                sendBytes = sendto(sockfd, buff, sizeof (buff), 0, (struct sockaddr *) &(p->elm), len);
            }
            close_all(clients);
        }
        else{
            for(clientaddr p = clients->next; p != NULL; p = p->next){
                if (p->elm.sin_port != client.sin_port){
                    xuli(buff);
                    sendBytes = sendto(sockfd, buff, sizeof (buff), 0, (struct sockaddr *) &(p->elm), len);
                    if (sendBytes < 0){
                        printf("Lỗi gửi ở client-%s\n", p->elm.sin_zero);
                    }
                }
                else{
                    sendBytes = sendto(sockfd, success_msg, sizeof (success_msg), 0, (struct sockaddr *) &(p->elm), len);
                }
            }
        }

    }
    memset(buff, 0, sizeof(buff));
    close(sockfd);
    return 0;
}