#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


void getFile(char *filename, char *buffer3){
    char buffer[1024] = {0};
	
	FILE *f;
	char c;
	// catch un-exist file
	f = fopen(filename, "r");
	if (f == NULL) {
        printf("Error in file open\n");
    }
    // count the line
	char buffer2[100];
    strcpy(buffer3,"");
	int count = 0;
	for (c = getc(f); c != EOF; c = getc(f)){
        //strcat(buffer3, c);
		if (c == '\n'){
			count = count + 1;
		}
	}
	fclose(f);
	
	f = fopen(filename, "r");
	// send data of file
	for(int i=0;i< count + 1;i++){
		fscanf(f,"%[^\n]\n",buffer2);
        strcat(buffer3, buffer2);
        strcat(buffer3,"\n");
		}
	int len = strlen(buffer3);
	strncpy(buffer3,buffer3,len-2);
	buffer3[strlen(buffer3)-1] = '\0';
	fclose(f);
    //printf("BUFFER3\n%s\n",buffer3);
     
}

