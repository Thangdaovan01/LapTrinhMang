#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "acc.h"

#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */
#define BUFF_SIZE 1024



int main()
{
    Node* head = NULL;
	Account acc[50], acc1;
	char user_name[30], pass[10], res[10];
	int n,i=0,count=0;

	FILE *p;
	p=fopen("account.txt","r");
	if (p== NULL){
		printf("Cannot open %s.\n", "account.txt");
		//return;
    } 
	
	while(fscanf(p,"%s %s %d\n",acc[i].username,acc[i].password,&acc[i].status) != EOF){
		head = addEnd(head,acc[i]);
		i++;
	}
    displayList(head);

    
 
	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[BUFF_SIZE], recv_data2[BUFF_SIZE], recv_data3[BUFF_SIZE], recv_data4[BUFF_SIZE];
	int bytes_sent, bytes_received, bytes_received2, bytes_received3;
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
		while(1){
			//receives message from client
			bytes_received = recv(conn_sock, recv_data, BUFF_SIZE-1, 0); //blocking
			if (bytes_received <= 0){
				printf("\nConnection closed");
				break;
			}
			else{
				recv_data[bytes_received] = '\0';
				printf("\nReceive: %s.", recv_data);
			}

            bytes_received2 = recv(conn_sock, recv_data2, BUFF_SIZE-1, 0); //blocking
			if (bytes_received2 <= 0){
				printf("\nConnection closed");
				break;
			}
			else{
				recv_data2[bytes_received2] = '\0';
				printf("\nReceive2: %s ", recv_data2);
			}
			
            //Check
            if(checkUsername(head,recv_data) == 0){
                    strcpy(recv_data3, "Cannot find account");
					//send to client
					bytes_sent = send(conn_sock, recv_data3, strlen(recv_data3), 0); /* send to the client welcome message */
					if (bytes_sent <= 0){
						printf("\nConnection closed");
						break;
					}
                }else{
                    if(checkStatus(head, recv_data) == 0){
                        strcpy(recv_data3, "Account is blocked or inactive");
						//send to client
						bytes_sent = send(conn_sock, recv_data3, strlen(recv_data3), 0); /* send to the client welcome message */
						if (bytes_sent <= 0){
							printf("\nConnection closed");
							break;
						}
                    }else{
                        do{
							//printf("\nauwdgsh\n");
							if(checkAccount(head,recv_data,recv_data2) == 0){
                                strcpy(recv_data3, "Password is incorrect. Please try again");
                                count++;
                            }else{
                                strcpy(recv_data3, "Login is successful!");
                                break;
                            }

							//send to client
							bytes_sent = send(conn_sock, recv_data3, strlen(recv_data3), 0); /* send to the client welcome message */
							if (bytes_sent <= 0){
								printf("\nConnection closed");
								break;
							}
							//printf("\n%d\n",count);
							//receive from client
							bytes_received3 = recv(conn_sock, recv_data4, BUFF_SIZE-1, 0); //blocking
							if (bytes_received3 <= 0){
								printf("\nConnection closed");
								break;
							}
							else{
								recv_data4[bytes_received3] = '\0';
								printf("\nReceive2: %s ", recv_data4);
							}
							
                            
                        }while(count<2);
                        if(count == 2){
                            blockAccount(head,recv_data);
                            //printAllAccount(p);
                            //printf("Password is incorrect. Account is blocked\n");
                            strcpy(recv_data3, "Password is incorrect. Account is blocked");
							//send to client
							bytes_sent = send(conn_sock, recv_data3, strlen(recv_data3), 0); /* send to the client welcome message */
							if (bytes_sent <= 0){
								printf("\nConnection closed");
								break;
							}
						}
                    }
                }









			
			//echo to client
			//bytes_sent = send(conn_sock, recv_data3, strlen(recv_data3), 0); /* send to the client welcome message */
			/*if (bytes_sent <= 0){
				printf("\nConnection closed");
				break;
			}
			*/
		}//end conversation
		close(conn_sock);	
	}
	
	close(listen_sock);
	return 0;
}
