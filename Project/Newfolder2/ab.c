#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int checkAnswer2(char *answer1){
    if((strcmp(answer1,"A")==0) || (strcmp(answer1,"B")==0) || (strcmp(answer1,"C")==0) || (strcmp(answer1,"D")==0) || (strcmp(answer1,"H")==0) || (strcmp(answer1,"S")==0)){
        return 1;
    }
    return 0;
}
int main(){
    char answer1[10];
    do{
        printf("\nNhap dap an: ");
	    scanf("%s",answer1);
        printf("Dap an 1: %s\n",answer1);
        if(strcmp(answer1, "E")==0) break;
        else if(strcmp(answer1, "H")==0) printf("Help!");
        else printf("Answer\n");
    }while(checkAnswer2(answer1)==0);
    //while((strcmp(answer1,"A")!=0) || (strcmp(answer1,"B")!=0) || (strcmp(answer1,"C")!=0) || (strcmp(answer1,"D")!=0) || (strcmp(answer1,"H")!=0) || (strcmp(answer1,"S")!=0));
	/*
    printf("\nNhap dap an: ");
	scanf("%s",answer1);
    printf("%d\n",checkAnswer2(answer1));
    */
    return 0;			
}