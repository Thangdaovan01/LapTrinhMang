#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../lib/question.h"

int main(){
    printf("ABCD\n");
    Question *head;
    readQuestionFromFile(&head);
    printListQuestion(&head);
    return 0;
}