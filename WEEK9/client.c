#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <string.h>
#define BUFF_SIZE 1024

int main(int argc, const char * argv[]) {
    //create a socket
    int network_socket;
    network_socket=socket(AF_INET,SOCK_STREAM,0);
    
    //specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9999);
    server_address.sin_addr.s_addr=INADDR_ANY;
    
    int connection_status = connect(network_socket, (struct sockaddr *) & server_address, sizeof(server_address));
    //check for connection_status
    if(connection_status==-1)
    {
        printf("The connection has error\n\n");
    }
    
    if(connection_status==0)
    {
	char response[256];
    //receive data from the server
    while(1){
	//char response[256];
    	recv(network_socket, &response, sizeof(response), 0);
        //printf("%s\n", response);
	    printf("enter a message to echo\n");
        memset(response,'\0',(strlen(response)+1));
	    fgets(response, BUFF_SIZE, stdin);	
        response[strlen(response)-1]='\0';
	    //scanf("%s",&response);
    	int send_status= send(network_socket,response, sizeof(response),0);
        //printf("%d\n",send_status);
	    //if (strcmp(response,"exit")==0){break;}
        if((strcmp(response,"q")==0) || (strcmp(response,"Q")==0)){
            printf("%d\n",send_status);
            break;}
    	//print out the server's response
        recv(network_socket, &response, sizeof(response), 0);
    	printf("Here is the echo message from the server: %s\n\n", response);
    }
	}
    //close the socket
    close(network_socket);
    
    return 0;
}
