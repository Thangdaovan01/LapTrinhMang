#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "Game.h"

#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */
#define BUFF_SIZE 1024

int main()
{
	Node *head = NULL;
	printf("AI LA TRIEU PHU \n");

    docFileTxt(&head);
	char sendbuff[BUFF_SIZE], send_buff[BUFF_SIZE];
	xuatMotCauHoi(head,send_buff);
	send_buff[strlen(send_buff)-1] = '\0';
	printf("\n%s\n",send_buff);
	
 
	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[BUFF_SIZE];
	int bytes_sent, bytes_received, bytes_received1;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	int sin_size;
	
	//Step 1: Construct a TCP socket to listen connection request
	if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		perror("\nError: ");
		return 0;
	}
	
	//Step 2: Bind address to socket
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   
	if(bind(listen_sock, (struct sockaddr*)&server, sizeof(server))==-1){ /* calls bind() */
		perror("\nError: ");
		return 0;
	}     
	
	//Step 3: Listen request from client
	if(listen(listen_sock, BACKLOG) == -1){  /* calls listen() */
		perror("\nError: ");
		return 0;
	}
	
	//Step 4: Communicate with client
	while(1){
		//accept request
		sin_size = sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,( struct sockaddr *)&client, &sin_size)) == -1) 
			perror("\nError: ");
  
		printf("You got a connection from %s\n", inet_ntoa(client.sin_addr) ); /* prints client's IP */
		
		//start conversation
		//while(1){
			char menu[500], choice[3], batDauTroChoi[100], ketQuaChungCuoc[300];
			int count;
			
			do{
				strcpy(menu,"\n\n\t\t\t\t\t==== MENU NGUOI CHOI  ====");
				strcat(menu,"\n\t\t\t\t\t=  1. BAT DAU TRO CHOI   =");
				strcat(menu,"\n\t\t\t\t\t=     NHAP 0 DE THOAT    =\n");
				strcat(menu,"\t\t\t\t\t========== END ===========\n");
				menu[strlen(menu)-1]='\0';	

				bytes_sent = send(conn_sock, menu, BUFF_SIZE-1, 0); // send to the client welcome message 
				if (bytes_sent <= 0){
					printf("\nConnection closed");
					break;
				}	


				bytes_received = recv(conn_sock, recv_data, BUFF_SIZE-1, 0); //blocking
				if (bytes_received <= 0){
					printf("\nConnection closed");
					break;
				}
				else{
					recv_data[bytes_received] = '\0';
					printf("\nReceive: %s ", recv_data);
				}
				strcpy(choice,recv_data);
				choice[strlen(choice)-1]='\0';
				printf("\nReceive menu: a%s b%ld", choice, strlen(choice));
				
				if(strcmp(choice,"1")==0){
					 //	BatDau();
					 	strcpy(batDauTroChoi,"\n----BAT DAU TRO CHOI----\n");
						strcat(batDauTroChoi,"Ban chi duoc nhap 4 dap an theo quy dinh la: (A} (B) (C) (D) hoac nhap (H) de nhan quyen tro giup hoac nhap (R) de dung cuoc choi va bao luu so tien thuong\n\n");
			            batDauTroChoi[strlen(batDauTroChoi)]='\0';
						printf("\n%s\n",batDauTroChoi);
						
						bytes_sent = send(conn_sock, batDauTroChoi, BUFF_SIZE-1, 0); // send to the client welcome message 
						if (bytes_sent <= 0){
							printf("\nConnection closed");
							break;
						}

						//count = BatDauTraLoi(head);

						//show ketqua
						strcpy(ketQuaChungCuoc,"\n----KET QUA CHUNG CUOC----\n");
						strcat(ketQuaChungCuoc,"So cau tra loi dung cua ban la: ");
						char a[50];
						sprintf(a,"%d",soCauTraLoiDung);
						strcat(ketQuaChungCuoc,a);
						strcat(ketQuaChungCuoc,"/15 cau\n");
						strcat(ketQuaChungCuoc,"Moc tra loi dung cua ban la: ");
						sprintf(a,"%d",count);
						strcat(ketQuaChungCuoc,a);
						strcat(ketQuaChungCuoc,"/15 cau\n");
						strcat(ketQuaChungCuoc,"So tien thuong cua ban la: ");
						sprintf(a,"%.0f",TinhThangTienThuong(count));
						strcat(ketQuaChungCuoc,a);
						strcat(ketQuaChungCuoc," VND\n");
						ketQuaChungCuoc[strlen(ketQuaChungCuoc)-1] = '\0';
			            
						bytes_sent = send(conn_sock, ketQuaChungCuoc, BUFF_SIZE-1, 0); // send to the client welcome message 
						if (bytes_sent <= 0){
							printf("\nConnection closed");
							break;
						}

			            /*if(count==15)
			            {
			            	//TextColor(30);
            				printf("Xin chuc mung ban da vuot tat ca cac cau hoi cua chung toi va ban da tro thanh trieu phu cua chuong trinh\n");
            				//TextColor(14);
            			}*/
						break;
				}else if(strcmp(choice,"0")==0){
					exit(1);
            		break;
				}else{
					printf("\nBan da chon tinh nang khong hop le. Moi ban vui long nhap lai\n");
					break;
         		}
        	}while(strcmp(choice,"0")!=0);











/*
			//receives message from client
			bytes_received = recv(conn_sock, recv_data, BUFF_SIZE-1, 0); //blocking
			if (bytes_received <= 0){
				printf("\nConnection closed");
				break;
			}
			else{
				recv_data[bytes_received] = '\0';
				printf("\nReceive: %s ", recv_data);
			}
*/
			/*xuatMotCauHoi(head,send_buff);
			send_buff[strlen(send_buff)-1] = '\0';
			printf("\n%s\n",send_buff);*/
			
/*			//echo to client
			bytes_sent = send(conn_sock, send_buff, strlen(send_buff), 0); // send to the client welcome message 
			if (bytes_sent <= 0){
				printf("\nConnection closed");
				break;
			}
*/			
		//}//end conversation
		close(conn_sock);	
	}
	
	close(listen_sock);
	return 0;
}
