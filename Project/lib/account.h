#ifndef __ACCOUNT__
#define __ACCOUNT__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BLOCKED 0
#define ACTIVE 1

#define ONLINE 1
#define OFFLINE 0

#define ADMIN 0
#define PLAYER 1
typedef struct
{
    char username[30];
    char password[30];
    int position; // 0: admin (1 admin) 1: player (>1 player)
    int status;  //1 online  0 offline
    int accountStatus; //1: active     0: blocked
    //int countSignIn;
    int score;
    int maxScore;
    struct Account *next;
} Account;

Account **createLinkList();                                                                       //Init link list NULL
Account *findUserNameAccount(Account **head, char *username);                                     // find Account By Username
//Account *findUserNameAccountByPosition(Account **head, int position);                             // find account by position
Account *newAccount(char *username, char *password, int accountStatus, int position);             // create node
void addAccount(Account **head, char *username, char *password, int accountStatus, int position); //add node to link list
//int countMemberOnline(Account **head, int *numberPLayerArray);                                    //count member online and save position into array
void printListAccount(Account **head);                                                            // print link list

void blockAccount(Account **head, char *username);  //change status of account to block
//void signinAccount(Account **head, char *username); //change status to login
#endif