#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

//Remember to use -pthread when compiling this server's source code
void *connection_handler(void *);

void my_strupr(char *x){
	for(int i=0; i<strlen(x); i++){
		if(x[i]>=97 && x[i]<=122){
			x[i] = x[i]-32;
		}
	}
}

int checkString(char *p){
	int n=strlen(p);
	int count=0;
	for(int i=0; i<n; i++){
		if(isalpha(p[i]) != 0 || p[i] == ' ') //la chu
			count++;
	}
	if(n==count) return 1;
	return 0;
}


int main()
{
    char server_message[100] = "Hello from Server!!\n";
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
    if (server_socket==-1){
	perror("Socket initialisation failed");
	exit(EXIT_FAILURE);
	}
    else
	printf("Server socket created successfully\n");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    //bind the socket to the specified IP addr and port
    if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr))!=0){
	printf("socket bind failed...\n"); 
        exit(0);
	}
    else
	printf("Socket successfully binded..\n"); 
    
    if (listen(server_socket, 3)!=0){
		printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    
    int no_threads=0;  //CUA CLIENT ket noi
    pthread_t threads[3];
    while (no_threads<3){  // 3 client
	printf("Listening...\n");
	int client_socket = accept(server_socket, NULL, NULL);
	puts("Connection accepted");
	if( pthread_create( &threads[no_threads], NULL ,  connection_handler , &client_socket) < 0){
	perror("Could not create thread");
	return 1;}
    	if (client_socket < 0) { 
        	printf("server acccept failed...\n"); 
        	exit(0); 
    		} 
    	else
        	printf("Server acccept the client...\n");
	puts("Handler assigned"); //ket noi thanh cong
	no_threads++;
	}
	int k=0;
    for (k=0;k<3;k++){
	pthread_join(threads[k],NULL);  //
}

    //int send_status;
    //send_status=send(client_socket, server_message, sizeof(server_message), 0);
    close(server_socket);
    
    return 0;
}


void *connection_handler(void *client_socket){ //xu ly ket noi ntn
	int socket = *(int*) client_socket;
	int read_len;
	char server_message[100]="Hello from server\n";
	int send_status;
    	send_status=send(socket, server_message, sizeof(server_message), 0);
	char client_message[100];
	while( (read_len=recv(socket,client_message, 100,0))>0)
	{
		//end of string marker
		//printf("read_len %d\n",read_len);
		client_message[read_len] = '\0';
		if((strcmp(client_message,"q")==0) || (strcmp(client_message,"Q")==0)){break;}
		if(checkString(client_message)==0){
			strcpy(client_message, "Wrong text format");
		}else{
			my_strupr(client_message);
		}
		//printf("%s\n",client_message);
		//Send the message back to client
		send_status=send(socket , client_message , strlen(client_message),0);	
	}
	
	return 0;
}

