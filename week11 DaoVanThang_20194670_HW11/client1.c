#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include "send_receiveFile.h"
/*
gcc tcp_client1.c -o tcp_client1
./tcp_client
*/

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5500
#define BUFF_SIZE 1024

/*typedef struct{
	int opcode;
	int length;
	char payload[BUFF_SIZE];
} Message;

int receiveMessage(int connfd, Message* message);
int sendMessage(int connfd, Message* message);
void receiveFile(int connfd, FILE* output);
void sendFile(int connfd, FILE* input);
*/
int main(){
	int client_sock;
	char buff[BUFF_SIZE + 1], buff1[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_received;
	
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
	int choice, ret;
	Message message;
	FILE *f;
	FILE *f_mahoa;
	FILE *f_giaima;
	char fileName[BUFF_SIZE];
	//send message
	printf("\n1. Ma hoa\n2. Giai ma\n3. Thoat\n->Lua chon cua ban la:");
	scanf("%d",&choice);
	printf("Nhap khoa: ");
	scanf("%s", message.payload);
	//message.payload[strlen(message.payload)]='\0';
	//printf("%s\n", message.payload);
	switch(choice)
	{
		case 1: //ma hoa
			message.opcode = 0;
			sendMessage(client_sock, &message);
			printf("Nhap ten file can ma hoa: ");
			scanf("%s",fileName);
			//printf("%ld\n",strlen(fileName));
			//fileName[strlen(fileName)-1]='\0';
			f = fopen(fileName, "r");
			if (f == NULL) {
				printf("Error in file open\n");
				break;
			}
			sendFile(client_sock, f); //gui file cho server
			fclose(f);
			
			//gui thong diep sau khi gui file thanh cong
			message.opcode==2;
			message.length==0;
			sendMessage(client_sock, &message);

			//nhan file da ma hoa
			f_mahoa = fopen("mahoa_client.txt","w");
			receiveFile(client_sock, f_mahoa);
			fclose(f_mahoa);

			//nhan thong diep
			ret = receiveMessage(client_sock, &message);
			printf("%d\n",message.opcode);
			printf("Qua trinh ma hoa thanh cong\n");
			break;
		
		case 2:
			message.opcode = 1;
			sendMessage(client_sock, &message);
			printf("Nhap ten file can giai ma: ");
			scanf("%s",fileName);
			f = fopen(fileName, "r");
			if (f == NULL) {
				printf("Error in file open\n");
				break;
			}
			sendFile(client_sock, f); //gui file cho server
			fclose(f);

			//gui thong diep sau khi gui file thanh cong
			message.opcode==2;
			message.length==0;
			sendMessage(client_sock, &message);

			//nhan file da giai ma
			f_giaima = fopen("giaima_client.txt","w");
			receiveFile(client_sock, f_giaima);
			fclose(f_giaima);

			//nhan thong diep
			ret = receiveMessage(client_sock, &message);
			printf("%d\n",message.opcode);
			printf("Qua trinh giai ma thanh cong\n");
			break;
		
		case 3:
		printf("Ban da thoat\n");
			break;
		default:
			printf("Lua chon khong hop le\n");
			break;
	}
	/*memset(buff,'\0',(strlen(buff)+1));
	fgets(buff, BUFF_SIZE, stdin);		
	msg_len = strlen(buff);
	printf("length %d\n",msg_len);
		
	bytes_sent = send(client_sock, buff, msg_len, 0);
	if(bytes_sent < 0)
		perror("\nError: ");
	
	//receive echo reply
	bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
	if (bytes_received < 0)
			perror("\nError: ");
	else if (bytes_received == 0)
			printf("Connection closed.\n");
		
	buff[bytes_received] = '\0';
	printf("Reply from server: %s\n", buff);

	if(strcmp(buff,"Khong hop le")!= 0){
		printf("\nNhap key:");
		memset(buff1,'\0',(strlen(buff)+1));
		fgets(buff1, BUFF_SIZE, stdin);		
		msg_len = strlen(buff1);
			
		bytes_sent = send(client_sock, buff1, msg_len, 0);
		if(bytes_sent < 0)
			perror("\nError: ");

		printf("\nNhap string:");
		memset(buff1,'\0',(strlen(buff)+1));
		fgets(buff1, BUFF_SIZE, stdin);		
		msg_len = strlen(buff1);
			
		bytes_sent = send(client_sock, buff1, msg_len, 0);
		if(bytes_sent < 0)
			perror("\nError: ");
		
			//receive echo reply
		bytes_received = recv(client_sock, buff1, BUFF_SIZE, 0);
		if (bytes_received < 0)
				perror("\nError: ");
		else if (bytes_received == 0)
				printf("Connection closed.\n");
			
		buff[bytes_received] = '\0';
		printf("Sau khi ma hoa, giai ma: %s\n", buff1);
	
	}*/
	
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
