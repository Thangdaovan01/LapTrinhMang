#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "message.h"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 12345
#define BUFF_SIZE 1024

int main(){
	int client_sock;
	char buff[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_received;
	ssize_t bytes_read;
	struct iovec iov[2];
	Message mess;
	
	//Step 1: Construct socket
	client_sock = socket(AF_INET,SOCK_STREAM,0);
	
	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	
	//Step 3: Request to connect server
	if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0){
		printf("\nError!Can not connect to sever! Client exit imediately! ");
		return 0;
	}
		
	//Step 4: Communicate with server			
	
	//send message
	while(1){
	//do{
	//while(strcmp(buff,"\n")!=0){
		printf("\nInsert string to send:");
		memset(buff,'\0',(strlen(buff)+1));
		fgets(buff, BUFF_SIZE, stdin);		
		msg_len = strlen(buff);
		printf("%d\n", msg_len);
		if(msg_len==1) break;
			
		bytes_sent = send(client_sock, buff, msg_len, 0);
		if(bytes_sent < 0)
			perror("\nError: ");

		bytes_received = receiveMessage(client_sock, &mess);
		printf("%s\n%s\n",mess.number,mess.str1);
		
		//receive echo reply
		/*bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
		if (bytes_received < 0)
				perror("\nError: ");
		else if (bytes_received == 0)
				printf("Connection closed.\n");
			
		buff[bytes_received] = '\0';
		printf("Reply from server: %s", buff);
		*/
		//bytes_read = readv(client_sock, iov, 2);
		
		//bytes_read = readv(client_sock, buff1, 3);
		//char *number = iov[0].iov_base;
		//printf("Reply from server:\nSo: %s\nChu: %s\n",buff1.number,buff1.str1);
		//iov[0].iov_base;
		//printf("Reply from server:\nSo: %p\nChu: %p\n", iov[0].iov_base, iov[1].iov_base);
	}//while(strcmp(buff,"\n")!=0);
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
