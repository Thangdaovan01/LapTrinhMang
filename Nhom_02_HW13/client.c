#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "acc.h"
#include "ceasar.h"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5550
#define BUFF_SIZE 1024

int main(int argc, char *argv[]){
	if(argc!=4){
		printf("Please input IP address and port number\n");
		return 0;
	}
	char *ip_address = argv[1];
	char *port_number = argv[2];
	int port = atoi(port_number);
	char *secretkey = argv[3];
	int key = atoi(secretkey);
	
	FILE *f1;
	FILE *f2;
	int client_sock;
	char buff[BUFF_SIZE + 1], mess[BUFF_SIZE + 1], allmess[BUFF_SIZE + 1], username[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_sent2, bytes_received;
	char duoifile[10];
	
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
		printf("\nInsert name: ");
		memset(username,'\0',(strlen(username)+1));
		fgets(username, BUFF_SIZE, stdin);		
		msg_len = strlen(username);
		username[msg_len - 1] = '\0';
		maHoaText(username, key);
						
		bytes_sent = send(client_sock, username, msg_len, 0);
		if(bytes_sent < 0)
			perror("\nError: ");
		
		while(1){
			//Printf all message in group chat
			bytes_received = recv(client_sock, allmess, BUFF_SIZE, 0);
			if (bytes_received < 0)
				perror("\nError: ");
			else if (bytes_received == 0)
				printf("Connection closed22.\n");
			allmess[bytes_received] = '\0';
			giaiMaText(allmess, key);
			printf("\n%s", allmess);

			/*
			f1 = fopen("groupchat.txt","r");
			f2 = fopen("groupchatClient.txt","w");
			giaiMaFile(f1, f2, key);
			printf("\n2. ABCDEF\n");
			fclose(f1);
			fclose(f2);

			readFile("groupchatClient.txt", allmess);
			printf("\n3. ABCDEF\n");
			printf("\n%s\n", allmess);	
			*/		
			//Nhan tin
			//do{
				printf("\nInsert string to send:");
				memset(mess,'\0',(strlen(mess)+1));
				fgets(mess, BUFF_SIZE, stdin);		
				msg_len = strlen(mess);
				mess[msg_len-1] = '\0';
				/*if(check_file_format(mess,"txt") == 1){
					f1 = fopen(mess,"r");
					f2 = fopen("filemahoaoclient.txt","w");
					maHoaFile(f1,f2,key);
					fclose(f1);
					fclose(f2);
					f2 = fopen("filemahoaoclient.txt","2");
					sendFile(client_sock,f2,mess);
					fclose(f2);
				}else{*/
					maHoaText(mess, key);
					bytes_sent = send(client_sock, mess, msg_len, 0);
					if(bytes_sent < 0)
						perror("\nError: ");
				//}
				
				
			//}while(strcmp(mess,"00")!=0);
		}
	
	
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
