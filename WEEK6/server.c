#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include "acc.h"

#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */
#define BUFF_SIZE 1024
#define FILE_SIZE 500
void *client_fun(void * fd);

int main(int argc, char *argv[])
{
	if(argc<2){
		printf("Please input port number\n");
		return 0;
	}
	
	char *port_number = argv[1];
	int port = atoi(port_number);

	Node* head = NULL;
	Node* head1=NULL;
	Image img[50], img1[50];
	char name[50];
	int n,i=0,count=0;


//file server_image
	FILE *p;
	p=fopen("server_image.txt","r");
	if (p== NULL){
		printf("Cannot open %s.\n", "server_image.txt");
		//return;
    } 
	
	while(fscanf(p,"%s %s\n",img[i].filename,img[i].filepath) != EOF){
		head = addEnd(head,img[i]);
		i++;
	}
    displayList(head);
	
// file client_image
	FILE *p1;
	p1=fopen("client_image.txt","r");
	if (p1== NULL){
		printf("Cannot open %s.\n", "client_image.txt");
		//return;
    } 
	while(fscanf(p1,"%s %s\n",img1[i].filename, img1[i].filepath) != EOF){
		head1 = addEnd(head1,img1[i]);
		i++;
	}
    displayList(head1);
	fclose(p1);
	fclose(p);



	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[BUFF_SIZE], send_data[BUFF_SIZE];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	int sin_size;
	pthread_t thread_id;
	char filepath[BUFF_SIZE];
	
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
				printf("\nReceive: %s ", recv_data);
			}

			if(checkFilename(head1,recv_data) == 1){
                    strcpy(send_data, "File Already Exists!");
					//send to client
					bytes_sent = send(conn_sock, send_data, strlen(send_data), 0); 
					if (bytes_sent <= 0){
						printf("\nConnection closed");
						break;
					}
					break;
			}else{

				if(checkFilenameFormat(recv_data) == 0){
						strcpy(send_data, "Error: Wrong File Format!");
						//send to client
						bytes_sent = send(conn_sock, send_data, strlen(send_data), 0); /* send to the client welcome message */
						if (bytes_sent <= 0){
							printf("\nConnection closed");
							break;
						}
						break;
				}else{

					if(checkFilename(head,recv_data) == 0){
							strcpy(send_data, "Error: File Not Found!");
							//send to client
							bytes_sent = send(conn_sock, send_data, strlen(send_data), 0); /* send to the client welcome message */
							if (bytes_sent <= 0){
								printf("\nConnection closed");
								break;
							}
							break;
					}else{
						/*pthread_create(&thread_id, NULL, client_fun, (void *)&conn_sock);  
            			pthread_detach(thread_id);*/
						Node* p=head;
						while(p!=NULL){
							if(strcmp(p->data.filename, recv_data) == 0)
								strcpy(filepath,p->data.filepath);
							p = p->next;
						}

						do {
							char *buffer    = NULL;
							int buffer_size = 0;
							int newsockfd;
							FILE* fp = fopen(filepath, "wb");

							if (fp == NULL) {
								//error("Error opening file");
								//printf("Cannot open %s.\n", filepath);
								strcpy(send_data, "Cannot open ");
								strcat(send_data, filepath);
								bytes_sent = send(conn_sock, send_data, strlen(send_data), 0); /* send to the client welcome message */
								if (bytes_sent <= 0){
									printf("\nConnection closed");
									break;
								}
								break;
							}

							n = read(conn_sock, &buffer_size, sizeof(int));//Read incoming data streams
							if(n < 0)
								error("Error reading size from Client");
							printf("%d", buffer_size);
							buffer = malloc(buffer_size);
							n = read(conn_sock, buffer, buffer_size);
							if(n < buffer_size)
								//error("Error reading file from Client");
								printf("\nF");
							fwrite(buffer, buffer_size, 1, fp);
							fclose(fp);
						} while(0);


						strcpy(send_data, "File Transfer Is Completed…");
						//send to client
						bytes_sent = send(conn_sock, send_data, strlen(send_data), 0); /* send to the client welcome message */
						if (bytes_sent <= 0){
							printf("\nConnection closed");
							break;
						}
						break;
					}
				}
			}
			/*int file_fp = open("C/Users/Admin/Downloads/seoul.png", O_RDONLY);
			if(file_fp<0) 
            { 
            	printf("\nFile %s Not Found\n", recv_data);
			}
			*/

			//echo to client
			bytes_sent = send(conn_sock, recv_data, bytes_received, 0); /* send to the client welcome message */
			if (bytes_sent <= 0){
				printf("\nConnection closed");
				break;
			}
		}//end conversation
		//close(newsockfd);
		close(conn_sock);	
	}
	
	close(listen_sock);
	return 0;
}

