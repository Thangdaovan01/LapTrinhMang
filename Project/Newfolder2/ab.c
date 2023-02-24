#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "account.h"

#define BUFF_SIZE 1024

int main(){
    Account *account1 = (Account *)malloc(sizeof(Account));
    readAccountFromFile(&account1);
    printListAccount(&account1);
    
    return 0;			
}