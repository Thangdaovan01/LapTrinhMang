#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check_file_format(char *fname){
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
	if(strcmp(ext,"txt") == 0)
		return 1;
	return 0;
}

int main(){
    printf("Khong la file\n");
    char name[20];
    strcpy(name, "abc");
    printf("%s\n", name);
    int i=check_file_format(name);
    if(i==0)
        printf("Khong la file\n");
    else printf("Day la file\n");
    return 0;
}