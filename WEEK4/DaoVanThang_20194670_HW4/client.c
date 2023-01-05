/*UDP Echo Client*/
#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLINE 1000
#define BUFF_SIZE 1024

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
 
int main(int argc, char *argv[]) 
{
	if(argc!=3){
		printf("Please input IP address and port number\n");
		return 0;
	}
	
	char *ip_address = argv[1];
	char *port_number = argv[2];
	int port = atoi(port_number);

	int client_sock, n; 
	struct sockaddr_in server_addr; 

    if ((client_sock=socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){  /* calls socket() */
		perror("\nError: ");
		exit(0);
	}
	
	// clear servaddr xac dinh dia chi may chu
	bzero(&server_addr, sizeof(server_addr)); 
	server_addr.sin_addr.s_addr = inet_addr(ip_address); 
	server_addr.sin_port = htons(port); 
	server_addr.sin_family = AF_INET; 

	// create datagram socket 
	//sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	// connect to server 
	if(connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	} 

	do {
		int g= 0, sin_size, bytes_sent, bytes_received;
		char buffer[100];
		char message[100];
		// get message
		printf("Input data: ");
        memset(message,'\0',(strlen(message)+1));
	    fgets(message, BUFF_SIZE, stdin);

		if (!checkBuff(message)){
                printf("\n\tError!\n");
                continue;
            }

        sin_size = sizeof(struct sockaddr);
        bytes_sent = sendto(client_sock, message, strlen(message), 0, (struct sockaddr *) &server_addr, sin_size);
        if(bytes_sent < 0){
            perror("Error: ");
            close(client_sock);
            return 0;
        }

        bytes_received = recvfrom(client_sock, buffer, BUFF_SIZE - 1, 0, (struct sockaddr *) &server_addr, &sin_size);
        if(bytes_received < 0){
            perror("Error: ");
            close(client_sock);
            return 0;
        }
        buffer[bytes_received] = '\0';
	
	}while(1);	
	// close the descriptor 
	close(client_sock); 
	return 0;
}