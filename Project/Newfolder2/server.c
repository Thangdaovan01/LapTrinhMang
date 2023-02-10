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
#include "question.h"
#include "account.h"
#include "protocol.h"

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

	Request *request = (Request *)malloc(sizeof(Request));
    Response *response = (Response *)malloc(sizeof(Response));
	Account *account = (Account *)malloc(sizeof(Account));
    Account *account1 = (Account *)malloc(sizeof(Account));
    
	//readAccountFromFile(&account);
	char buff[BUFF_SIZE], username[BUFF_SIZE], password[BUFF_SIZE], mess[BUFF_SIZE];
	int bytes_sent, bytes_received, bytes_received1, checkAcc;
	while(1){
		readAccountFromFile(&account);
		//printListAccount(&account);
		receiveRequest(sockfd, request, sizeof(Request), 0);
		request->username[strlen(request->username)]='\0';
		printf("username: %s - password: %s - opcode: %d \n", request->username, request->pass, request->code);
		//if(request->code == 3)
		switch (request->code)
		{
		case 1:
			do{
				/* code */
				//printListAccount(&account);
				checkAcc = checkAccount(account,request->username, request->pass);
				printf("checkAcc: %d\n",checkAcc);
				response->code=checkAcc;
				setMessageResponse(response);
				printf("Mess: %s\n", response->message);
				sendResponse(sockfd, response, sizeof(Response),0);
				printf("Position: %d\n",account->position);
			}while(checkAcc!=1);	
			account1 = findUserNameAccount(&account, request->username);
			account1->status = 1;
			printf("Username: %s - Position: %d - Status: %d - Score: %d - MaxScore: %d\n",account1->username, account1->position, account1->status, account1->score, account1->maxScore);
			
			if(account1->position == 1){
				strcpy(buff, "Player");
			}else{
				strcpy(buff, "Admin");
			}
			bytes_sent = send(sockfd, buff, 10, 0); /* send to the client welcome message */
			if (bytes_sent <= 0){
				printf("\nConnection closed");
				break;
			}

			switch (account1->position)
			{
				case 0:
					printf("ADMIN\n");
					/* code */
					break;
				
				case 1:
					printf("PLAYER\n");
					/* code */
					break;

				default:
					break;
			}
			
			break;
			
		case 2:
			do{
				printListAccount(&account);
				printf("%s\n",request->username);
				checkAcc = checkUsername(account,request->username);
				printf("%d\n",checkAcc);
				response->code=checkAcc;
				setMessageResponse(response);
				printf("%s\n", response->message);
				sendResponse(sockfd, response, sizeof(Response),0);
			}while(checkAcc!=4);
			printInFile(request->username, request->pass);
			//readAccountFromFile(&account);	
			break;
		
		default:
			break;
		}
	}
	close(sockfd);
}