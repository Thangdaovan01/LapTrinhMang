#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "account.h"

#define BUFF_SIZE 1024

int main(){
    Account *account1 = (Account *)malloc(sizeof(Account));
    readAccountFromFile(&account1);
    //printListAccount(&account1);
    Account *acc = NULL;

    xepHangTop10();
 /* acc = findMaxScore(account1);
    printf("Username: %s\n", acc->username);
    printf("Pass: %s\n", acc->password);
    printf("Max Score: %d\n", acc->maxScore);
    //account1 = deleteAccount(account1, acc->username);
    deleteAcc(&account1, acc->username);
//    printListAccount(&account1);

    acc = findMaxScore(account1);
    printf("Username: %s\n", acc->username);
    printf("Pass: %s\n", acc->password);
    printf("Max Score: %d\n", acc->maxScore);
    deleteAcc(&account1, acc->username);
    //account1 = deleteAccount(account1, acc->username);
//    printListAccount(&account1);

    acc = findMaxScore(account1);
    printf("Username: %s\n", acc->username);
    printf("Pass: %s\n", acc->password);
    printf("Max Score: %d\n", acc->maxScore);
    deleteAcc(&account1, acc->username);
    //account1 = deleteAccount(account1, acc->username);
//    printListAccount(&account1);*/
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