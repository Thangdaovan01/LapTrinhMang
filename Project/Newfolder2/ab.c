#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFF_SIZE 1024
int checkAnswer2(char *answer1){
    if((strcmp(answer1,"A")==0) || (strcmp(answer1,"B")==0) || (strcmp(answer1,"C")==0) || (strcmp(answer1,"D")==0) || (strcmp(answer1,"H")==0) || (strcmp(answer1,"S")==0)){
        return 1;
    }
    return 0;
}

int checkInsertLevel(char *str){
    if((strcmp(str,"EASY")==0) || (strcmp(str,"NORMAL")==0) || (strcmp(str, "HARD")==0))
        return 1;
    return 0;
}

void insertQuestion1(char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *true_ans, char *wrong_ans1, char *wrong_ans2, char *level){
    printf("\nInsert question: ");
	memset(question,'\0',(strlen(question)+1));
	fgets(question, BUFF_SIZE, stdin);	
	question[strlen(question) - 1] = '\0';

    printf("\nInsert answer1: ");
	memset(answer1,'\0',(strlen(answer1)+1));
	fgets(answer1, BUFF_SIZE, stdin);	
	answer1[strlen(answer1) - 1] = '\0';

    printf("\nInsert answer2: ");
	memset(answer2,'\0',(strlen(answer2)+1));
	fgets(answer2, BUFF_SIZE, stdin);
	answer2[strlen(answer2) - 1] = '\0';

    printf("\nInsert answer3: ");
	memset(answer3,'\0',(strlen(answer3)+1));
	fgets(answer3, BUFF_SIZE, stdin);
	answer3[strlen(answer3) - 1] = '\0';

    printf("\nInsert answer4: ");
	memset(answer4,'\0',(strlen(answer4)+1));
	fgets(answer4, BUFF_SIZE, stdin);	
	answer4[strlen(answer4) - 1] = '\0';

    printf("\nInsert true_ans: ");
	memset(true_ans,'\0',(strlen(true_ans)+1));
	fgets(true_ans, BUFF_SIZE, stdin);	
	true_ans[strlen(true_ans) - 1] = '\0';

    printf("\nInsert wrong_ans1: ");
	memset(wrong_ans1,'\0',(strlen(wrong_ans1)+1));
	fgets(wrong_ans1, BUFF_SIZE, stdin);
	wrong_ans1[strlen(wrong_ans1) - 1] = '\0';

    printf("\nInsert wrong_ans2: ");
	memset(wrong_ans2,'\0',(strlen(wrong_ans2)+1));
	fgets(wrong_ans2, BUFF_SIZE, stdin);
	wrong_ans2[strlen(wrong_ans2) - 1] = '\0';

    do{
        printf("\nInsert level: ");
        memset(level,'\0',(strlen(level)+1));
        fgets(level, BUFF_SIZE, stdin);	
        level[strlen(level) - 1] = '\0';
    }while(checkInsertLevel(level)==0);

}

int main(){
    
    char question[BUFF_SIZE], answer1[BUFF_SIZE], answer2[BUFF_SIZE], answer3[BUFF_SIZE], answer4[BUFF_SIZE], level[10],  true_ans[5], wrong_ans1[5], wrong_ans2[5];
	
    insertQuestion1(question,answer1, answer2,answer3,answer4,true_ans,wrong_ans1,wrong_ans2,level);
    printf("Question: %s\n",question);
    printf("answer1: %s\n",answer1);
    printf("answer2: %s\n",answer2);
    printf("answer3: %s\n",answer3);
    printf("answer4: %s\n",answer4);
    printf("True answer: %s\n",true_ans);
    printf("Wrong answer1: %s\n",wrong_ans1);
    printf("Wrong answer2: %s\n",wrong_ans2);
    printf("Level: %s\n",level);
    return 0;			
}