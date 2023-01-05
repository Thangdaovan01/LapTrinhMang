#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "getFile.h"


#define PORT 5550
#define BACKLOG 20
#define BUFF_SIZE 1024

/* Handler process signal*/
void sig_chld(int signo);

/*
* Receive and echo message to client
* [IN] sockfd: socket descriptor that connects to client 	
*/
void echo(int sockfd);
void toUp(char *p);

int main(){
	
	int listen_sock, conn_sock; /* file descriptors */
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	pid_t pid;
	int sin_size;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		return 0;
	}
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listen_sock, (struct sockaddr*)&server, sizeof(server))==-1){ 
		perror("\nError: ");
		return 0;
	}     

	if(listen(listen_sock, BACKLOG) == -1){  
		perror("\nError: ");
		return 0;
	}
	
	/* Establish a signal handler to catch SIGCHLD */
	signal(SIGCHLD, sig_chld); //thay doi

	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock, (struct sockaddr *)&client, &sin_size))==-1){
			if (errno == EINTR)  //check dung dot ngot
				continue;
			else{
				perror("\nError: ");			
				return 0;
			}
		}
		
		/* For each client, fork spawns a child, and the child handles the new client */
		pid = fork();  //tao tien trinh con
		
		/* fork() is called in child process */
		if(pid  == 0){
			close(listen_sock);  //dong listen cua ttrinh con va in ra dia chi ip cua client
			printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
			echo(conn_sock);	 // xu ly				
			exit(0);
		}
		
		/* The parent closes the connected socket since the child handles the new client */
		close(conn_sock);
	}
	close(listen_sock);
	return 0;
}

void sig_chld(int signo){
	pid_t pid;
	int stat;
	
	/* Wait the child process terminate */
	while((pid = waitpid(-1, &stat, WNOHANG))>0)  //doc ttrinh con xem co doi trang thai va xem ttrinh con nao dong lai
		printf("\nChild %d terminated\n",pid);
}

void toUp(char *p){
    while(*p){
        *p=toupper(*p);
        p++;
    }
}

void echo(int sockfd) {
	/*char buff[BUFF_SIZE];
	int bytes_sent, bytes_received;
	
	bytes_received = recv(sockfd, buff, BUFF_SIZE, 0); //blocking
	if (bytes_received < 0)
		perror("\nError: ");
	else if (bytes_received == 0)
		printf("Connection closed.");
	
	bytes_sent = send(sockfd, buff, bytes_received, 0); // echo to the client 
	if (bytes_sent < 0)
		perror("\nError: ");*/
	
    /*int valread = 0;
    int bytes_received;
	char buffer[1024] = {0};
	char only_string[100];
	char only_number[100];
	//valread = read( sockfd , buffer, 1024);
    bytes_received = recv(sockfd, buffer, BUFF_SIZE, 0);
    buffer[strlen(buffer) - 1] = '\0';
    printf("%s\n",buffer);
    FILE *f;
	int words = 0;
	char c;
	// catch un-exist file
	f = fopen(buffer, "r");
	if (f == NULL) {
    perror("Error in file open\n");
    }
    // count the line
	char buffer2[100], buffer3[100];
    strcpy(buffer3,"");
	int count = 0;
	for (c = getc(f); c != EOF; c = getc(f)){
        //strcat(buffer3, c);
		if (c == '\n'){
			count = count + 1;
		}
	}
	fclose(f);
	// send number of line in this file
	write(sockfd, &count, sizeof(int));
	f = fopen(buffer, "r");
	// send data of file
	for(int i=0;i< count + 1;i++){
		fscanf(f,"%[^\n]\n",buffer2);
        //printf("%s\n",buffer2);
        //buffer2 = strupr(buffer2);
        strcat(buffer3, buffer2);
        strcat(buffer3,"\n");
		write(sockfd,buffer2,100);
	}
	fclose(f);*/

    int bytes_sent, bytes_received;
	char buff[1024];
	bytes_received = recv(sockfd, buff, BUFF_SIZE, 0); //blocking
	if (bytes_received < 0)
		perror("\nError: ");
	else if (bytes_received == 0)
		printf("Connection closed.");
    buff[strlen(buff)-1]='\0';
	printf("BUFF\n%s\n",buff);
	
    char buffer3[100];
    getFile(buff, buffer3);
    //toUp(buffer3);
    printf("BUFFER3\n%s\n",buffer3);

    bytes_sent = send(sockfd, buffer3, strlen(buffer3), 0); // echo to the client 
	if (bytes_sent < 0)
		perror("\nError: ");

    /*f = fopen(buffer, "w");
    fprintf(f,"%s",buffer3);
    fclose(f);*/
	close(sockfd);
}
