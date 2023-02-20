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

void menuAdmin(){
	printf("===MENUADMIN====\n1. Them cau hoi\n2. Thoat\n===========\n");
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
	char enter;
	int client_sock, count = 0;
	char buff[BUFF_SIZE + 1], mess[BUFF_SIZE + 1], allmess[BUFF_SIZE + 1], username[BUFF_SIZE + 1], password[BUFF_SIZE + 1], answer1[10];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_sent2, bytes_received;
	int choose1, choose2;
	//char quest[BUFF_SIZE], answer1[BUFF_SIZE], answer2[BUFF_SIZE], answer3[BUFF_SIZE], answer4[BUFF_SIZE], level[10],  true_ans[5], wrong_ans1[5], wrong_ans2[5];
	Request *request = (Request *)malloc(sizeof(Request));
    Response *response = (Response *)malloc(sizeof(Response));
	Question *question = (Question *)malloc(sizeof(Question));
    RequestQuestion *requestQuestion = (RequestQuestion *)malloc(sizeof(RequestQuestion));
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
		menu1();
		printf("\nLua chon: ");
		scanf("%d", &choose1);
		scanf("%c",&enter);
		printf("%d\n", choose1);
		if(choose1 == 3) break;
		request->code=choose1;
		sendRequest(client_sock, request, sizeof(Request), 0);
					
		switch (choose1)
		{
			case 1:
				do{
					printf("\nInsert username: ");
					memset(username,'\0',(strlen(username)+1));
					fgets(username, BUFF_SIZE, stdin);	
					username[strlen(username)-1] = '\0';
					
					printf("\nInsert password: ");
					memset(password,'\0',(strlen(password)+1));
					fgets(password, BUFF_SIZE, stdin);	
					password[strlen(password)-1] = '\0';
					
					request->code = 01;
					strcpy(request->username, username);
					strcpy(request->pass, password);
					sendRequest(client_sock, request, sizeof(Request), 0);
					
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
					menuPlayer1();
					printf("Lua chon: ");
					scanf("%d",&choose2);
					scanf("%c",&enter);
					if(choose2==3) break;
					switch (choose2)
					{
					case 1:
					//gui yeu cau vs opcode = 3: chuan bi gui cau tra loi
						request->code=10;
						sendRequest(client_sock, request, sizeof(Request), 0);
					
						while(count < 15)
						{
							//server nhan request vs opcode=3 va gui 1 cau hoi cho client					
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
								printf("Mess: %s - So cau dung: %d - Tien: %d\n", response->message, response->socaudung, response->tienThuong);
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
									printf("Mess: %s - So cau dung: %d - Tien: %d\n", response->message, response->socaudung, response->tienThuong);
		
									break;
								} 
							}
							
							count++;
						}
						break;
					case 2: //xem bang xep hang
						request->code=5;
						sendRequest(client_sock, request, sizeof(Request), 0);

						for(int i=0; i<10; i++){
							receiveResponse(client_sock, response, sizeof(Response),0);
							printf("Top %d - Username: %s - Max Score: %d\n",response->rank,response->username,response->maxScore);		
						}
						break;

					default:
						break;
					}
					
				}
				if(strcmp(buff, "Admin")==0){
					while(1){
						menuAdmin();
						printf("Lua chon: ");
						scanf("%d",&choose2);
						scanf("%c",&enter);
						
						if(choose2==1){
							request->code=7;
							sendRequest(client_sock, request, sizeof(Request), 0);
							insertQuestion1(requestQuestion->question, requestQuestion->answer1, requestQuestion->answer2, requestQuestion->answer3, requestQuestion->answer4, requestQuestion->true_ans, requestQuestion->wrong_ans1, requestQuestion->wrong_ans2, requestQuestion->level);
							sendRequestQuestion(client_sock, requestQuestion, sizeof(RequestQuestion),0);
							//insertQuestion(requestQuestion->question, requestQuestion->answer1, requestQuestion->answer2, requestQuestion->answer3, requestQuestion->answer4, requestQuestion->tr);
						}

						if(choose2==2){
							//request->code=11;
							//sendRequest(client_sock, request, sizeof(Request), 0);
							break;
						} 
					}					
				}
				break;

			case 2:
				do{
					printf("\nInsert username to sign up: ");
					memset(username,'\0',(strlen(username)+1));
					fgets(username, BUFF_SIZE, stdin);	
					username[strlen(username)-1] = '\0';

					printf("\nInsert password to sign up: ");
					memset(password,'\0',(strlen(password)+1));
					fgets(password, BUFF_SIZE, stdin);	
					password[strlen(password)-1] = '\0';

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
