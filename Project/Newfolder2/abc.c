#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "question.h"
#include "account.h"
//#include "gameplay.h"

int main(){
    printf("ABCD\n");
    
    Question *head = NULL;
    printf("ABCDABCD\n");
    readQuestionFromFile(&head);
    printf("ABCD\n");
    //printListQuestion(&head);
    //xuatMotDanhSachCauHoi(head);
    Question *p=head;
    int sttcauDe = 0;
    while((p!=NULL) /*&& (strcmp(p->level, "EASY")==0)*/ && (sttcauDe < 5)){
        if(strcmp(p->level, "EASY")==0){
            printf("EASY\n");
            xuatMotCauHoi(p);
            printf("Answer is %s\n",p->true_ans);
            char answer[5];
            printf("Nhap answer: ");
            scanf("%s",answer);
            
            if(checkAnswer1(p,answer) ==0){
                printf("WRong answer\n");
            }else{
                printf("True Answer\n");
            }
            printf("ABCD\n");
            sttcauDe++;
        }
        p=p->next;
        
    }

    Question *p1=head;
    int sttcauTB = 0;
    while((p1!=NULL) /*&& (strcmp(p->level, "EASY")==0)*/ && (sttcauTB < 3)){
        if(strcmp(p1->level, "NORMAL")==0){
        printf("NORMAL\n");
        xuatMotCauHoi(p1);
        printf("Answer is %s\n",p1->true_ans);
        char answer[5];
        printf("Nhap answer: ");
        scanf("%s",answer);
        
        if(checkAnswer1(p1,answer) ==0){
            printf("WRong answer\n");
        }else{
            printf("True Answer\n");
        }
        printf("ABCD\n");
        sttcauTB++;
        }
        p1=p1->next;
        
    }
    Question *p2=head;
    int sttcauKho = 0;
    while((p2!=NULL) /*&& (strcmp(p->level, "EASY")==0)*/ && (sttcauKho < 3)){
        if(strcmp(p2->level, "HARD")==0){
        printf("HARD\n");
        xuatMotCauHoi(p2);
        printf("Answer is %s\n",p2->true_ans);
        char answer[5];
        printf("Nhap answer: ");
        scanf("%s",answer);
        
        if(checkAnswer1(p2,answer) ==0){
            printf("WRong answer\n");
        }else{
            printf("True Answer\n");
        }
        
        sttcauKho++;
        }
        p2=p2->next;
        
    }

/*
    Account *head = NULL;
    readAccountFromFile(&head);
    printf("ABCD\n");
    printListAccount(&head);
*/
    return 0;
}