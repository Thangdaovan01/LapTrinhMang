#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "question.h"
#include "account.h"
#include "protocol.h"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5550
#define BUFF_SIZE 1024

void menu1(){
	printf("===MENU====\n1. Dang nhap\n2. Dang ky\n3. Thoat\n===========\n");
}

void menuPlayer1(){
	printf("===MENU====\n1. Bat dau choi\n2. Xem bang xep hang\n3. Thoat\n===========\n");
}

int main(int argc, char *argv[]){
	if(argc!=3){
		printf("Please input IP address and port number\n");
		return 0;
	}
	char *ip_address = argv[1];
	char *port_number = argv[2];
	int port = atoi(port_number);
	
	FILE *f1;
	FILE *f2;
	int client_sock, count = 0;
	char buff[BUFF_SIZE + 1], mess[BUFF_SIZE + 1], allmess[BUFF_SIZE + 1], username[BUFF_SIZE + 1], password[BUFF_SIZE + 1], answer1[10];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_sent2, bytes_received;
	int choose1, choose2;
	Request *request = (Request *)malloc(sizeof(Request));
    Response *response = (Response *)malloc(sizeof(Response));
	Question *question = (Question *)malloc(sizeof(Question));
    
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
	/*		
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
			*/
	while(1){
		menu1();
		printf("\nLua chon: ");
		scanf("%d", &choose1);
		printf("%d\n", choose1);
		if(choose1 == 3) break;
		switch (choose1)
		{
			case 1:
				do{
					printf("\nInsert username: ");
					memset(username,'\0',(strlen(username)+1));
					//fgets(username, BUFF_SIZE, stdin);	
					scanf("%s",username);	
					msg_len = strlen(username);
					username[msg_len] = '\0';

					printf("\nInsert password: ");
					memset(password,'\0',(strlen(password)+1));
					//fgets(password, BUFF_SIZE, stdin);	
					scanf("%s",password);	
					msg_len = strlen(password);
					password[msg_len] = '\0';

					request->code = 01;
					strcpy(request->username, username);
					strcpy(request->pass, password);
					sendRequest(client_sock, request, sizeof(Request), 0);
					/* code */

					receiveResponse(client_sock, response, sizeof(Response),0);
					printf("%s\n", response->message);
				}while(response->code != 1);

				bytes_received = recv(client_sock, buff, BUFF_SIZE-1, 0); //blocking
				if (bytes_received <= 0){
					printf("\nConnection closed");
					break;
				}
				buff[strlen(buff)]='\0';
				printf("Receive: %s\n",buff);
				if(strcmp(buff,"Player")==0){
					while(count < 3)
					{
						receiveQuestion(client_sock,question,sizeof(Question),0);
						xuatMotCauHoi(question);
						printf("Nhap cac dap an A, B, C, D. Nhap H de nhan su tro giup. Nhap S de dung cuoc choi\n");
						printf("COUNT: %d\n", count);
					
						do{
							printf("\nNhap dap an: ");
							scanf("%s",answer1);
							answer1[strlen(answer1)]='\0';
							//printf("Dap an ban chon: %s\n", answer1);
							//printf("Dap an 1: %s\n",answer1);
							if(strcmp(answer1,"H")==0){
								strcpy(request->answer,answer1);
								request->code = 04;
								sendRequest(client_sock, request, sizeof(Request), 0);
								receiveResponse(client_sock, response, sizeof(Response),0);
								printf("Help: %s\n", response->data);
		
							}
							//printf("DAP ANNNNNNNN\n");
						}while(checkAnswer2(answer1)==0);
						//printf("2DAP ANNNNNNNN\n");
						strcpy(request->answer,answer1);
						
						if(strcmp(answer1,"S")==0){
							request->code = 06;
							sendRequest(client_sock, request, sizeof(Request), 0);
							receiveResponse(client_sock, response, sizeof(Response),0);
							printf("Mess: %s Tien: %d\n", response->message, response->tienThuong);
							break;
						}else if((strcmp(answer1,"A")!=0) || (strcmp(answer1,"B")!=0) || (strcmp(answer1,"C")!=0) || (strcmp(answer1,"D")!=0)){
							request->code = 03;
							
							// Gui dap an
							sendRequest(client_sock, request, sizeof(Request), 0);
							//Nhan ket qua tra ve sau khi gui dap an
							receiveResponse(client_sock, response, sizeof(Response),0);
							printf("%s\n", response->message);
							if(response->code == 6){
								printf("True answer\n");
							}else{
								printf("Wrong answer\n");
								receiveResponse(client_sock, response, sizeof(Response),0);
								printf("Mess: %s Tien: %d\n", response->message, response->tienThuong);
	
								break;
							} 
						}
						
						count++;
					}
				}
				break;

			case 2:
				do{
					printf("\nInsert username to sign up: ");
					memset(username,'\0',(strlen(username)+1));
					//fgets(username, BUFF_SIZE, stdin);	
					scanf("%s",username);	
					msg_len = strlen(username);
					username[msg_len] = '\0';

					printf("\nInsert password to sign up: ");
					memset(password,'\0',(strlen(password)+1));
					//fgets(password, BUFF_SIZE, stdin);	
					scanf("%s",password);	
					msg_len = strlen(password);
					password[msg_len] = '\0';

					request->code = 02;
					strcpy(request->username, username);
					strcpy(request->pass, password);
					sendRequest(client_sock, request, sizeof(Request), 0);
					
					receiveResponse(client_sock, response, sizeof(Response),0);
					printf("%s\n", response->message);
				}while(response->code != 4);
				break;
			
			default:
				//printf("\nInsert username to sign up: ");
				break;
		}
	}
	
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
