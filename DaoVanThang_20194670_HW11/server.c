#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/select.h> 
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "ceasar.h"
#include "send_receiveFile.h"

/*
gcc select_server1.c -o select_server1
./select_server1
*/

#define PORT 5500   /* Port that will be opened */ 
#define BACKLOG 20   /* Number of allowed connections */
#define BUFF_SIZE 1024

/* The processData function copies the input string to output */
void processData(int sockfd, Message *message);

/* The recv() wrapper function*/
int receiveData(int s, char *buff, int size, int flags);

/* The send() wrapper function*/
int sendData(int s, char *buff, int size, int flags);

int main()
{
	int i, maxi, maxfd, listenfd, connfd, sockfd, key;
	int nready, client[FD_SETSIZE];
	ssize_t	ret, ret1;
	fd_set	readfds, allset, checkfds, writefds, exceptfds;
	char sendBuff[BUFF_SIZE], rcvBuff[BUFF_SIZE], rcvBuff1[BUFF_SIZE], result[BUFF_SIZE];
	socklen_t clilen;
	Message message;
	struct sockaddr_in cliaddr, servaddr;

	//Step 1: Construct a TCP socket to listen connection request
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		perror("\nError: ");
		return 0;
	}

	//Step 2: Bind address to socket
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(PORT);

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1){ /* calls bind() */
		perror("\nError: ");
		return 0;
	} 

	//Step 3: Listen request from client
	if(listen(listenfd, BACKLOG) == -1){  /* calls listen() */
		perror("\nError: ");
		return 0;
	}

	maxfd = listenfd;			/* initialize */
	maxi = -1;				/* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;			/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	
	//Step 4: Communicate with clients
	while (1) {
		readfds = allset;		/* structure assignment */
		nready = select(maxfd+1, &readfds, NULL, NULL, NULL);
		if(nready < 0){
			perror("\nError: ");
			return 0;
		}
		//check the status of listenfd
		// neu co client ket noi
		if (FD_ISSET(listenfd, &readfds)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			if((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0)
				perror("\nError: ");
			else{
				printf("You got a connection from %s\n", inet_ntoa(cliaddr.sin_addr)); /* prints client's IP */
				for (i = 0; i < FD_SETSIZE; i++)
					if (client[i] < 0) {
						client[i] = connfd;	/* save descriptor */
						break;
					}
				if (i == FD_SETSIZE){
					printf("\nToo many clients");
					close(connfd);
				}

				FD_SET(connfd, &allset);	/* add new descriptor to set */
				if (connfd > maxfd)
					maxfd = connfd;		/* for select */
				if (i > maxi)
					maxi = i;		/* max index in client[] array */

				if (--nready <= 0)
					continue;		/* no more readable descriptors */
			}
		}

		for (i = 0; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &readfds)) {
				ret = receiveMessage(sockfd, &message);
				if (ret <= 0){
					FD_CLR(sockfd, &allset);
					close(sockfd);
					client[i] = -1;
				}
				
				else {
					processData(sockfd, &message);
					if (ret <= 0){
						FD_CLR(sockfd, &allset);
						close(sockfd);
						client[i] = -1;
					}
				}

				if (--nready <= 0)
					break;		/* no more readable descriptors */
			}
		}
	}
	
	return 0;
}

void processData(int sockfd, Message *message){
	int key = 0;
	int ret;
	Message message1;
	FILE *p;        //file tam de luu xu ly ma hoa, giai ma khi nhan duoc tu client
	FILE *p_mahoa;
	FILE *p_giaima;

	key = atoi(message->payload);
	p = fopen("tmp.txt","w");
	receiveFile(sockfd, p);
	fclose(p);
	ret = receiveMessage(sockfd, &message1);

	if(message->opcode == 0){
		//xu ly viec ma hoa o phia server
		p = fopen("tmp.txt","r");
		p_mahoa = fopen("mahoa_server.txt","w");
		maHoa(p, p_mahoa, key);
		fclose(p);
		fclose(p_mahoa);

		//tien hanh gui file da ma hoa cho client
		p_mahoa = fopen("mahoa_server.txt","r");
		sendFile(sockfd, p_mahoa);
		fclose(p_mahoa);

		//gui thong diep sau khi gui file thanh cong
		message1.opcode = 2;
		message1.length = 0;
		//strcpy((&message)->payload, "Qua trinh ma hoa hoan tat");
		sendMessage(sockfd, &message1);

	}else if(message->opcode == 1){
		//xu ly viec giai ma o phia server
		p = fopen("tmp.txt","r");
		p_giaima = fopen("mahoa_server.txt","w");
		maHoa(p, p_giaima, key);
		fclose(p);
		fclose(p_giaima);

		//tien hanh gui file da giai ma cho client
		p_giaima = fopen("mahoa_server.txt","r");
		sendFile(sockfd, p_giaima);
		fclose(p_giaima);

		//gui thong diep sau khi gui file thanh cong
		message1.opcode =2;
		message1.length=0;
		//strcpy(message->payload, "Qua trinh giai ma hoan tat");
		sendMessage(sockfd, &message1);
	}else{
		printf("Khong hop le!\n");
	}
}

int receiveData(int s, char *buff, int size, int flags){
	int n;
	n = recv(s, buff, size, flags);
	if(n < 0)
		perror("Error: ");
	return n;
}

int sendData(int s, char *buff, int size, int flags){
	int n;
	n = send(s, buff, size, flags);
	if(n < 0)
		perror("Error: ");
	return n;
}

