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
void ketThucStop(int sockfd, Account *acc);
void ketThucWrong(int sockfd, Account *acc);
void xemBangXepHang(int sockfd);
void player(int sockfd, Question *question, Account *account1);
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

void ketThucStop(int sockfd, Account *acc){
	Response *response = (Response *)malloc(sizeof(Response));
	
	int tienThuong = TinhTienThuong(acc);
	response->code = 14;
	setMessageResponse(response);
	response->tienThuong = tienThuong;
	response->socaudung = acc->numTrueAns;
	updateAccountList(acc, acc->numTrueAns);
	printf("Mess: %s - So cau dung: %d - Tien: %d\n", response->message, response->socaudung, response->tienThuong);
	sendResponse(sockfd, response, sizeof(Response),0);
				
}

void ketThucWrong(int sockfd, Account *acc){
	Response *response = (Response *)malloc(sizeof(Response));
	
	int tienThuong = TinhTienThuong2(acc);
	response->code = 14;
	setMessageResponse(response);
	response->tienThuong = tienThuong;
	response->socaudung = acc->numTrueAns;
	updateAccountList(acc, acc->numTrueAns);
	printf("Mess: %s - So cau dung: %d - Tien: %d\n", response->message, response->socaudung, response->tienThuong);
	sendResponse(sockfd, response, sizeof(Response),0);
				
}

void xemBangXepHang(int sockfd){
	Account *account1 = (Account *)malloc(sizeof(Account));
    readAccountFromFile(&account1);
    Account *acc=NULL;
    Response *response = (Response *)malloc(sizeof(Response));
	
    int i=0;
    for(i=0; i<10; i++){
        acc = findMaxScore(account1);
        printf("Username: %s\n", acc->username);
        printf("Pass: %s\n", acc->password);
        printf("Max Score: %d\n", acc->maxScore);
        response->rank = i+1;
		strcpy(response->username, acc->username);
		response->maxScore = acc->maxScore;
		sendResponse(sockfd, response, sizeof(Response),0);
        deleteAcc(&account1, acc->username);
    } 
    
}

void player(int sockfd, Question *question, Account *account1){
	Request *request = (Request *)malloc(sizeof(Request));
    Response *response = (Response *)malloc(sizeof(Response));
	Question *q = NULL;
	Question *q1 = question;
	Question *q2 = question;
	Question *q3 = question;
	int countEasy=0, countNormal=0, countHard = 0, checkAns, tienThuong;
	
	while((q1!=NULL) && (countEasy<5)){
		if(strcmp(q1->level, "EASY")==0){
			q = q1;
			sendQuestion(sockfd, q, sizeof(Question),0);
			countEasy++;
			do{
				receiveRequest(sockfd, request, sizeof(Request), 0);
				printf("CODE: %d - ANSWER: %s\n", request->code, request->answer);
			
				if(strcmp(request->answer,"H")==0){
					//CODE
					response->code = 12;
					//printf("NumHelp: %d\n",account1->numHelp);
					if(account1->numHelp > 0){
						strcpy(response->data, "Dap an sai la: ");
						strcat(response->data, q->wrong_ans1);
						strcat(response->data, " va ");
						strcat(response->data, q->wrong_ans2);	
					}else{
						strcpy(response->data, "Da het quyen tro giup");
					}
					sendResponse(sockfd, response, sizeof(Response),0);
					account1->numHelp = account1->numHelp-1;
				}
			}while(checkAnswer2(request->answer)==0);
			
			if(strcmp(request->answer,"S")==0){
				//CODE
				printf("username: %s - password: %s - opcode: %d \n", request->username, request->pass, request->code);
				printf("Account Stop\n");
				ketThucStop(sockfd, account1);
			}else{
				checkAns = checkAnswer1(q, request->answer);
				printf("request Ans: %s - checkAns: %d\n",request->answer,checkAns);
				response->code=checkAns;
				setMessageResponse(response);
				printf("Mess: %s\n", response->message);
				sendResponse(sockfd, response, sizeof(Response),0);
						
				if(checkAns == 6){ //true answer
					account1->numTrueAns++;
				}else{
					printf("Wrong answer\n");
					printf("Num of Answer: %d\n", account1->numTrueAns);
					ketThucWrong(sockfd, account1);
					break;
				} 
			}
					
		}
		q1 = q1->next;
	}

	while((q2!=NULL) && (countNormal<5)){
		if(strcmp(q2->level, "NORMAL")==0){
			sendQuestion(sockfd, q2, sizeof(Question),0);
			countNormal++;
			do{
				//Nhan dap an tu client
				receiveRequest(sockfd, request, sizeof(Request), 0);
				printf("CODE: %d - ANSWER: %s\n", request->code, request->answer);
				printf("True ANswer: %s\n", q2->true_ans);
				if(strcmp(request->answer,"H")==0){
					//CODE
					response->code = 12;
					if(account1->numHelp > 0){
						strcpy(response->data, "Dap an sai la: ");
						strcat(response->data, q2->wrong_ans1);
						strcat(response->data, " va ");
						strcat(response->data, q2->wrong_ans2);	
					}else{
						strcpy(response->data, "Da het quyen tro giup");
					}
					sendResponse(sockfd, response, sizeof(Response),0);
					account1->numHelp = account1->numHelp-1;
				}
			}while(checkAnswer2(request->answer)==0);
			if(strcmp(request->answer,"S")==0){
				//CODE
				printf("username: %s - password: %s - opcode: %d \n", request->username, request->pass, request->code);
				printf("Account Stop\n");
				ketThucStop(sockfd, account1);
			}else{
				checkAns = checkAnswer1(q2, request->answer);
				printf("checkAns: %d\n",checkAns);
				response->code=checkAns;
				setMessageResponse(response);
				printf("Mess: %s\n", response->message);
				sendResponse(sockfd, response, sizeof(Response),0);
						
				if(checkAns == 6){ //true answer
					account1->numTrueAns++;
				}else{
					printf("Wrong answer\n");
					printf("Num of Answer: %d\n", account1->numTrueAns);
					ketThucWrong(sockfd, account1);
					break;
				} 
			}
					
		}
		q2 = q2->next;
	}

	while((q3!=NULL) && (countHard<5)){
		if(strcmp(q3->level, "HARD")==0){
			//q = q3;
			sendQuestion(sockfd, q3, sizeof(Question),0);
			countHard++;
			do{
				receiveRequest(sockfd, request, sizeof(Request), 0);
				printf("CODE: %d - ANSWER: %s\n", request->code, request->answer);
			
				if(strcmp(request->answer,"H")==0){
					//CODE
					response->code = 12;
					if(account1->numHelp > 0){
						strcpy(response->data, "Dap an sai la: ");
						strcat(response->data, q3->wrong_ans1);
						strcat(response->data, " va ");
						strcat(response->data, q3->wrong_ans2);	
					}else{
						strcpy(response->data, "Da het quyen tro giup");
					}
					sendResponse(sockfd, response, sizeof(Response),0);
					account1->numHelp = account1->numHelp-1;
				}
			}while(checkAnswer2(request->answer)==0);
			if(strcmp(request->answer,"S")==0){
				//CODE
				printf("username: %s - password: %s - opcode: %d \n", request->username, request->pass, request->code);
				printf("Account Stop\n");
				ketThucStop(sockfd, account1);
			}else{
				checkAns = checkAnswer1(q3, request->answer);
				printf("checkAns: %d\n",checkAns);
				response->code=checkAns;
				setMessageResponse(response);
				printf("Mess: %s\n", response->message);
				sendResponse(sockfd, response, sizeof(Response),0);
						
				if(checkAns == 6){ //true answer
					account1->numTrueAns++;
				}else{
					printf("Wrong answer\n");
					printf("Num of Answer: %d\n", account1->numTrueAns);
					ketThucWrong(sockfd, account1);
					break;
				} 
			}
					
		}
		q3 = q3->next;
	}
	
}

void echo(int sockfd) {
	char user_name[30], res[10];
	int n,i=0,count=0;
	int countEasy=0, countNormal=0, countHard=0;

	Request *request = (Request *)malloc(sizeof(Request));
    Response *response = (Response *)malloc(sizeof(Response));
	Account *account = (Account *)malloc(sizeof(Account));
    Account *account1 = (Account *)malloc(sizeof(Account));
    Question *question = (Question *)malloc(sizeof(Question));
    readQuestionFromFile(&question);
	RequestQuestion *reQuestion1 = (RequestQuestion *)malloc(sizeof(RequestQuestion));
	RequestQuestion *reQuestion2 = (RequestQuestion *)malloc(sizeof(RequestQuestion));
	Question *q = question;
	Question *q1 = NULL;
	//readAccountFromFile(&account);
	char buff[BUFF_SIZE], username[BUFF_SIZE], password[BUFF_SIZE], mess[BUFF_SIZE];
	int bytes_sent, bytes_received, bytes_received1, checkAcc, checkAns;
	while(1){
		readAccountFromFile(&account);
		receiveRequest(sockfd, request, sizeof(Request), 0);
		
		switch (request->code)
		{
		case 1:
				
			do{
				//nhan request bao gom username, password tu phia client
				receiveRequest(sockfd, request, sizeof(Request), 0);
				request->username[strlen(request->username)]='\0';
				printf("username: %s - password: %s - opcode: %d \n", request->username, request->pass, request->code);
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
			printf("Username: %s - Position: %d - Status: %d - Score: %d - MaxScore: %d - Num: %d\n",account1->username, account1->position, account1->status, account1->score, account1->maxScore, account1->numTrueAns);
			
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

			//switch (account1->position)
			if(account1->position==0) 
			{

				//case 0:
				while(1){
					//printf("ADMIN\n");
					receiveRequest(sockfd, request, sizeof(Request), 0);
					
					if(request->code==7){ //neu yeu cau nhap cau hoi
						receiveRequestQuestion(sockfd, reQuestion1, sizeof(RequestQuestion), 0);
						printf("Question: %s\n",reQuestion1->question);
						printf("answer1: %s\n",reQuestion1->answer1);
						printf("answer2: %s\n",reQuestion1->answer2);
						printf("answer3: %s\n",reQuestion1->answer3);
						printf("answer4: %s\n",reQuestion1->answer4);
						printf("True answer: %s\n",reQuestion1->true_ans);
						printf("Wrong answer1: %s\n",reQuestion1->wrong_ans1);
						printf("Wrong answer2: %s\n",reQuestion1->wrong_ans2);
						printf("Level: %s\n",reQuestion1->level);
						printQuestionInFile(reQuestion1->question,reQuestion1->answer1, reQuestion1->answer2,reQuestion1->answer3,reQuestion1->answer4,reQuestion1->true_ans,reQuestion1->wrong_ans1,reQuestion1->wrong_ans2,reQuestion1->level);
					}else{
						printf("ADMIN BREAK\n");
						break;
					}
				}

			}else if(account1->position==1){
				printf("PLAYER\n");
				account1->numHelp = 3;
				receiveRequest(sockfd, request, sizeof(Request), 0);
				if(request->code==10){ //neu yeu cau gui cau tra loi
					player(sockfd,q,account1);
				}
				if(request->code==5){ //neu yeu cau xem bang xep hang
					xemBangXepHang(sockfd);	
				}
			}	//break;
							
			break;
			
		case 2:
			
			//readAccountFromFile(&account);
			do{
				receiveRequest(sockfd, request, sizeof(Request), 0);
				request->username[strlen(request->username)]='\0';
				printf("username: %s - password: %s - opcode: %d \n", request->username, request->pass, request->code);
				
				//printListAccount(&account);
				//printf("%s\n",request->username);
				checkAcc = checkUsername(account,request->username);
				printf("checkAcc: %d\n",checkAcc);
				response->code=checkAcc;
				setMessageResponse(response);
				printf("%s\n", response->message);
				sendResponse(sockfd, response, sizeof(Response),0);
			}while(checkAcc!=4);
			if(checkAcc ==4) printInFile(request->username, request->pass);
			//readAccountFromFile(&account);	
			break;
		
		default:
			break;
		}
	}
	close(sockfd);
}