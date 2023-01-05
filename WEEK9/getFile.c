#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define BUFF_SIZE 1024

void toUp(char *p){
    while(*p){
        *p=toupper(*p);
        p++;
    }
}

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

int main(){
    
    //getFile("a1.txt");
		char response[256];
 		printf("enter a message to echo\n");
        memset(response,'\0',(strlen(response)+1));
	    fgets(response, BUFF_SIZE, stdin);	
        response[strlen(response)-1]='\0';

		printf("%d\n", checkString(response));

		my_strupr(response);
		printf("%s\n",response);
/*char buffer[1024] = {0};
	
	FILE *f;
	char c;
	// catch un-exist file
	f = fopen("week7.txt", "r");
	if (f == NULL) {
        printf("Error in file open\n");
    }
    // count the line
	char buffer2[100], buffer3[100];
    strcpy(buffer3,"");
	int count = 0;
	for (c = getc(f); c != EOF; c = getc(f)){
        //strcat(buffer3, c);
		if (c == '\n'){
			count = count + 1;
		}
	}
	fclose(f);
	
	f = fopen("week7.txt", "r");
	// send data of file
	for(int i=0;i< count + 1;i++){
		fscanf(f,"%[^\n]\n",buffer2);
        strcat(buffer3, buffer2);
        strcat(buffer3,"\n");
		}
	fclose(f);
    printf("BUFFER3\n%s\n",buffer3);*/

    return 0;
}