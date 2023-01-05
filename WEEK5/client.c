#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5550
#define BUFF_SIZE 8192

int main(){
	int client_sock, count=0;
	char buff[BUFF_SIZE], buff2[BUFF_SIZE], buff3[BUFF_SIZE], buff4[BUFF_SIZE];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, msg_len2, msg_len3, bytes_sent,bytes_sent2, bytes_sent3, bytes_received;
	
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
	while(1){
		//send message
		printf("\nInsert name account:");
		memset(buff,'\0',(strlen(buff)+1));
		//fgets(buff, BUFF_SIZE, stdin);		
        scanf("%s",buff);
		msg_len = strlen(buff);
		if (msg_len == 0) break;

		bytes_sent = send(client_sock, buff, msg_len, 0);
		if(bytes_sent <= 0){
			printf("\nConnection closed!\n");
			break;
		}


		printf("\nInsert password:");
		memset(buff2,'\0',(strlen(buff)+1));
		//fgets(buff2, BUFF_SIZE, stdin);	
		scanf("%s",buff2);	
		msg_len2 = strlen(buff2);
		if (msg_len2 == 0) break;

		bytes_sent2 = send(client_sock, buff2, msg_len2, 0);
		if(bytes_sent2 <= 0){
			printf("\nConnection closed!\n");
			break;
		}

		//receive echo reply
		bytes_received = recv(client_sock, buff3, BUFF_SIZE-1, 0);
		if(bytes_received <= 0){
			printf("\nError!Cannot receive data from sever!\n");
			break;
		}
		
		buff3[bytes_received] = '\0';
		printf("Reply from server: %s", buff3);

        if(strcmp(buff3,"Password is incorrect. Please try again" ) == 0){
		//if(strcmp(buff3,"Password is incorrect. Account is blocked" ) == 0){
		do{
			//printf("abcdef");
			printf("\nInsert password:");
			memset(buff4,'\0',(strlen(buff4)+1));
			//fgets(buff2, BUFF_SIZE, stdin);	
			scanf("%s",buff4);	
			msg_len3 = strlen(buff4);
			if (msg_len3 == 0) break;

			bytes_sent3 = send(client_sock, buff4, msg_len3, 0);
			if(bytes_sent3 <= 0){
				printf("\nConnection closed!\n");
				break;
			}
			//receive from server
			bytes_received = recv(client_sock, buff3, BUFF_SIZE-1, 0);
			if(bytes_received <= 0){
				printf("\nError!Cannot receive data from sever!\n");
				break;
			}
		
			buff3[bytes_received] = '\0';
			printf("Reply from server: %s", buff3);
		}while(strcmp(buff3,"Password is incorrect. Account is blocked" ) != 0);
		}
	}
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
