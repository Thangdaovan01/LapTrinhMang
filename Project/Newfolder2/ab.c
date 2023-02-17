#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "account.h"

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

Account *deleteAccount(Account *acc, char *str){
    Account *p = acc;
    Account *p1= NULL;

    if(acc == NULL) return NULL;
    while(strcmp(p->username,str)!=0){
        if(p->next == NULL) return NULL;
        else{
            p1 = p;
            //p = p->next;
        }
        p = p->next;
    }
    /*while(p!=NULL){
        if(strcmp(p->username,str)!=0){
            p1 = p;
            p=p->next;
        }
    }*/
    //printListAccount(&p);
    if(p==acc){
        p = p->next;
    }else{
        p1->next = p->next;
    }
    return p;
}

Account *findMaxScore(Account *account1){
    //Account *account1 = (Account *)malloc(sizeof(Account));
    //readAccountFromFile(&account1);
    //printListAccount(&account1);
    Account *acc = NULL;
    Account *acc1 = account1->next;
    for(acc = account1->next; acc!=NULL; acc=acc->next){
        if(acc->maxScore > acc1->maxScore){
            acc1 = acc;
        }
    }
    printf("A\n\n");
    return acc1;
}

void xepHangTop10(){
    Account *account1 = (Account *)malloc(sizeof(Account));
    readAccountFromFile(&account1);
    Account *acc=NULL;
    //printListAccount(&account1);
    int i=0;
    for(i=0; i<5; i++){
        acc = findMaxScore(account1);
        printf("Username: %s\n", acc->username);
        printf("Pass: %s\n", acc->password);
        printf("Max Score: %d\n", acc->maxScore);
        
        account1 = deleteAccount(account1, acc->username);
    } 
}

int main(){
    Account *account1 = (Account *)malloc(sizeof(Account));
    readAccountFromFile(&account1);
    //printListAccount(&account1);
    Account *acc = NULL;

    //xepHangTop10();
    acc = findMaxScore(account1);
    printf("Username: %s\n", acc->username);
    printf("Pass: %s\n", acc->password);
    printf("Max Score: %d\n", acc->maxScore);
    account1 = deleteAccount(account1, acc->username);
//    printListAccount(&account1);

    acc = findMaxScore(account1);
    printf("Username: %s\n", acc->username);
    printf("Pass: %s\n", acc->password);
    printf("Max Score: %d\n", acc->maxScore);
    account1 = deleteAccount(account1, acc->username);
//    printListAccount(&account1);

    acc = findMaxScore(account1);
    printf("Username: %s\n", acc->username);
    printf("Pass: %s\n", acc->password);
    printf("Max Score: %d\n", acc->maxScore);
    account1 = deleteAccount(account1, acc->username);
//    printListAccount(&account1);
/*
    acc = findMaxScore(account1);
    printf("Username: %s\n", acc->username);
    printf("Pass: %s\n", acc->password);
    printf("Max Score: %d\n", acc->maxScore);
    account1 = deleteAccount(account1, acc->username);
    printListAccount(&account1);
*/   
    return 0;			
}