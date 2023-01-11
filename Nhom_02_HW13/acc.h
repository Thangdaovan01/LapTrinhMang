#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFF_SIZE 1024

void printInFile(char* username, char* mess){
	FILE *p;
	p = fopen("groupchat.txt","a");
	fprintf(p,"%s : %s\n", username, mess);
	fclose(p);
}

void readGroupchat(char *allmess){
	FILE *p;
	p = fopen("groupchat.txt","r");
	int i=0;
	char c;
	//fprintf(p,"%s : %s\n", username, mess);
	while ((c = fgetc(p)) != EOF)
    {
        allmess[i] = c;
        i++;
    }
    allmess[i]='\0';
    ///printf("String\n%s\n", allmess);
	fclose(p);
}

void readFile(char *filename, char *allmess){
	FILE *p;
	p = fopen(filename,"r");
	int i=0;
	char c;
	//fprintf(p,"%s : %s\n", username, mess);
	while ((c = fgetc(p)) != EOF)
    {
        allmess[i] = c;
        i++;
    }
    allmess[i]='\0';
    ///printf("String\n%s\n", allmess);
	fclose(p);
}

int check_file_format(char *fname, char *duoifile){
	char ext[6];
	int i=strlen(fname)-1;
	int k=0;
	do{
		i--;
	}
	while(fname[i]!='.' && i>0);
	if(i == 0) return 0;
	for(int j=i+1;j<=strlen(fname);j++){
		ext[k]=fname[j];
		k++;
	}
	//check
	if(strcmp(ext,duoifile) == 0)
		return 1;
	return 0;
}

void receiveFile(int connfd, FILE* output, char *filename) {
    fwrite(filename, sizeof(char), strlen(filename), output);
}

void sendFile(int connfd, FILE* input, char *filename) {
    //while (1) {
        int n = fread(filename, sizeof(char), BUFF_SIZE - 1, input);
       
}