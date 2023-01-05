#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5550
#define BUFF_SIZE 1024

int main(int argc, char *argv[]){
	if(argc!=5){
		printf("Please input IP address and port number\n");
		return 0;
	}
	char *ip_address = argv[1];
	char *port_number = argv[2];
	int port = atoi(port_number);
	char *username = argv[3];
	char *password = argv[4];
	//username[strlen(username)-1] = '\0';
	//password[strlen(password)-1] = '\0';
	//printf("\n1.%s\n", username);
	//printf("\n2.%s\n", password);

	int client_sock;
	char buff[BUFF_SIZE + 1], mess[BUFF_SIZE + 1], allmess[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_sent2, bytes_received;
	
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
	//while(1){
		//Send uasername and password
		//printf("Send username\n");
		bytes_sent = send(client_sock, username, strlen(username), 0);
		if(bytes_sent < 0)
			perror("\nError: ");
		//printf("%d\n",bytes_sent);

		bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
		if (bytes_received < 0)
				perror("\nError: ");
		else if (bytes_received == 0)
				printf("Connection closed.\n");
		buff[bytes_received] = '\0';
		//printf("Reply from server: %s", buff);
		
		//printf("Send password\n");
		bytes_sent2 = send(client_sock, password, strlen(password), 0);
		if(bytes_sent2 < 0)
			perror("\nError: ");
			//printf("%d\n",bytes_sent2);

		bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
		if (bytes_received < 0)
				perror("\nError: ");
		else if (bytes_received == 0)
				printf("Connection closed.\n");
		buff[bytes_received] = '\0';
		printf("Reply from server: %s", buff);
		//End send username and password

		//if(strcmp(buff, "Password is incorrect")==0) break;
		if(strcmp(buff, "Sign in Successful. You can chat with another people in chat room")==0){
			while(1){
			//Printf all message in group chat
			bytes_received = recv(client_sock, allmess, BUFF_SIZE, 0);
			if (bytes_received < 0)
					perror("\nError: ");
			else if (bytes_received == 0)
					printf("Connection closed22.\n");
			allmess[bytes_received] = '\0';
			printf("\n%s", allmess);
			//do{
				printf("\nInsert string to send:");
				memset(mess,'\0',(strlen(mess)+1));
				fgets(mess, BUFF_SIZE, stdin);		
				msg_len = strlen(mess);
						
				bytes_sent = send(client_sock, mess, msg_len, 0);
				if(bytes_sent < 0)
					perror("\nError: ");
			//}while(strcmp(mess,"00")!=0);
		}
	}
	//send message
	/*printf("\nInsert string to send:");
	memset(buff,'\0',(strlen(buff)+1));
	fgets(buff, BUFF_SIZE, stdin);		
	msg_len = strlen(buff);
		
	bytes_sent = send(client_sock, buff, msg_len, 0);
	if(bytes_sent < 0)
		perror("\nError: ");*/
	
	//receive echo reply
	/*bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
	if (bytes_received < 0)
			perror("\nError: ");
	else if (bytes_received == 0)
			printf("Connection closed.\n");
		
	buff[bytes_received] = '\0';
	printf("Reply from server: %s", buff);*/
	
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
