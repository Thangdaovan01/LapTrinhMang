#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "account.h"
#include "question.h"

void xuatMotCauHoi(Question **head)
{
    Question *p=*head;
    printf("%s\nA. %s\nB. %s\nC. %s\nD. %s\n",p->question,p->answer1,p->answer2,p->answer3,p->answer4);  
}

void xuatMotDanhSachCauHoi(Question **head)
{
    Question *p=*head;

    while(p!=NULL){
        //printf("%s\n%s\n%s\n%s\n%s\n",p->data.CauHoi,p->data.TraLoi.A,p->data.TraLoi.B,p->data.TraLoi.C,p->data.TraLoi.D);
        xuatMotCauHoi(p);
        p = p->next;
    }
}