/*UDP Echo Server*/
#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLINE 1000 

int split(char * buffer, char * number,char * string){
	
	// Only number in buffer converts to string only_number 
	strcpy(string,buffer);
	int k=0;
	strcpy(number,buffer);
	int j=0;

	// if number, copy to only_number
	// if character, copy to only_string
	int m = 0;
	for(int i=0; i<100 ;i++){
		char ch = number[i];
		if (ch == '\0') break;
		if(ch >= '0' && ch <= '9'){
    	    number[j] = ch;
    	   	j++;
   		}
   		else if ((ch >= 'a' && ch <= 'z')||(ch == ' ')){
   			string[k] = ch;
   			k++;
   		}
   		else{
   			return 0;
   		}
   	}
   	number[j] = '\0'; 
	string[k] = '\0'; 
	return 1;

}

// Driver code 
int main(int argc, char *argv[]) 
{ 
	// catch wrong input
	if(argc<2){
		printf("Please input port number\n");
		return 0;
	}
	
	char *port_number = argv[1];
	int port = atoi(port_number);
	char buffer1[100], buffer2[100];
	char only_string[100];
	char only_number[100];
	int len1, len2, server_sock, sin_size, bytes_received1, bytes_received2; 
	struct sockaddr_in server, client1, client2; 
	bzero(&server, sizeof(server)); 


/////
    if ((server_sock=socket(AF_INET, SOCK_DGRAM, 0)) == -1 ){  /* calls socket() */
		perror("\nError: ");
		exit(0);
	}
    
	server.sin_family = AF_INET;         
	server.sin_port = htons(port);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = INADDR_ANY;  /* INADDR_ANY puts your IP address automatically */   
	//bzero(&(server.sin_zero),8); /* zero the rest of the structure */

  
	if(bind(server_sock,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1){ /* calls bind() */
		perror("\nError: ");
		exit(0);
	} 
	
	while(1){
	//receive the datagram 
	len1 = sizeof(client1); 
	bytes_received1 = recvfrom(server_sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client1,&len1); //receive message from server 
	buffer1[bytes_received1] = '\0';

	len2 = sizeof(client2); 
	bytes_received2 = recvfrom(server_sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client2,&len2); //receive message from server 
	buffer2[bytes_received2] = '\0';

	// split data to only string and only number
	if (split(buffer1,only_number,only_string)!=1)
	{
		//puts("Error");
		strcpy(only_number,"Error");
		strcpy(only_string,"");

	}

	// send the response to client
	sendto(server_sock, only_number, MAXLINE, 0, (struct sockaddr*)&client2, sizeof(client2)); 
	sendto(server_sock, only_string, MAXLINE, 0, (struct sockaddr*)&client2, sizeof(client2)); 


	if (split(buffer2,only_number,only_string)!=1)
	{
		//puts("Error");
		strcpy(only_number,"Error");
		strcpy(only_string,"");

	}

	// send the response to client
	sendto(server_sock, only_number, MAXLINE, 0, (struct sockaddr*)&client1, sizeof(client1)); 
	sendto(server_sock, only_string, MAXLINE, 0, (struct sockaddr*)&client1, sizeof(client1)); 

}
} 
