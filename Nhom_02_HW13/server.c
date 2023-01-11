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
#include "acc.h"

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

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Please input IP address and port number\n");
		return 0;
	}
	char *port_number = argv[1];
	int portnumber = atoi(port_number);
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
	signal(SIGCHLD, sig_chld);

	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock, (struct sockaddr *)&client, &sin_size))==-1){
			if (errno == EINTR)
				continue;
			else{
				perror("\nError: ");			
				return 0;
			}
		}
		
		/* For each client, fork spawns a child, and the child handles the new client */
		pid = fork();
		
		/* fork() is called in child process */
		if(pid  == 0){
			close(listen_sock);
			printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
			echo(conn_sock);					
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
	while((pid = waitpid(-1, &stat, WNOHANG))>0)
		printf("\nChild %d terminated\n",pid);
}

void echo(int sockfd) {
	char user_name[30], res[10];
	int n,i=0,count=0;

	FILE *p1;
	FILE *p2;

	char buff[BUFF_SIZE], username[BUFF_SIZE], password[BUFF_SIZE], mess[BUFF_SIZE];
	int bytes_sent, bytes_received, bytes_received1;
//while(1){	
	//Receive username and password
	bytes_received = recv(sockfd, username, BUFF_SIZE, 0); //blocking
	if (bytes_received < 0)
		perror("\nError: ");
	else if (bytes_received == 0)
		printf("Connection closed.");
	username[bytes_received]='\0';
	//printf("%d\n",bytes_received);
	printf("\n1.%s\n", username);

	while(1){
		//Send Message in Group chat
			char allmess[1000];
			readGroupchat(allmess);
			bytes_sent = send(sockfd, allmess, strlen(allmess), 0); // send to the client welcome message 
			if (bytes_sent <= 0){
				printf("\nConnection closed");
				break;
			}
		//do{
			bytes_received = recv(sockfd, mess, BUFF_SIZE, 0); //blocking
			if (bytes_received < 0)
				perror("\nError: ");
			else if (bytes_received == 0){
				printf("Connection closed11.");
				break;
			}
			mess[bytes_received]='\0';
			printf("%s\n", mess);
			/*if(check_file_format(mess,"txt")==1){
				p1 = fopen("filenhanserver.txt","w");
				receiveFile(sockfd, p1, "filenhanserver.txt" );
				fclose(p1);
			}*/
			printInFile(username,mess);
		//}while(strcmp(mess,"00")!=0);
	}
			
	close(sockfd);
}