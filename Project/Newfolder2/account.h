//#ifndef __ACCOUNT__
//#define __ACCOUNT__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFF_SIZE 1024

#define BLOCKED 0
#define ACTIVE 1

#define ONLINE 1
#define OFFLINE 0

#define ADMIN 0
#define PLAYER 1
typedef struct account
{
    char username[30];
    char password[30];
    int position; // 0: admin (1 admin) 1: player (>1 player)
    int status;  //1 online  0 offline
    int accountStatus; //1: active     0: blocked
    //int countSignIn;
    int score;
    int maxScore;
    struct account *next;
}Account;

/*Account **createLinkList();                                                                       //Init link list NULL
Account *findUserNameAccount(Account **head, char *username);                                     // find Account By Username
//Account *findUserNameAccountByPosition(Account **head, int position);                             // find account by position
Account *newAccount(char *username, char *password, int accountStatus, int position);             // create node
void addAccount(Account **head, char *username, char *password, int accountStatus); //add node to link list
//int countMemberOnline(Account **head, int *numberPLayerArray);                                    //count member online and save position into array
void printListAccount(Account **head);                                                            // print link list
void splitAccountFromFile(char *input, char *position, char *username, char *password, char *account, char *score);
void blockAccount(Account **head, char *username);  //change status of account to block
//void signinAccount(Account **head, char *username); //change status to login
#endif
*/

Account **createLinkList()
{
    Account **head = (Account **)malloc(sizeof(Account *));
    *head = NULL;

    return head;
}

//find account by username
Account *findUserNameAccount(Account **head, char *username)
{
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(ptr->username, username) == 0)
            return ptr;
    }
    return NULL;
}
//create node
Account *newAccount(char *username, char *password, char *accountStatus, char *maxScore/*, int accountStatus, int position*/)
{
    Account *new1 = (Account *)malloc(sizeof(Account));
    strcpy(new1->username, username);
    strcpy(new1->password, password);
    /*new->accountStatus = accountStatus;
    new->position = position;
    new->status = OFFLINE;
    new->countSignIn = 0;
    new->next = NULL;*/
    new1->status = OFFLINE;
    new1->accountStatus = atoi(accountStatus);
    new1->position = PLAYER;
    new1->score = 0;
    new1->maxScore = atoi(maxScore);
    return new1;
}
//add node
void addAccount(Account **head, char *username, char *password, char *accountStatus,char *maxScore)
{
    Account *new1 = newAccount(username, password, accountStatus, maxScore);
    Account *current = (*head);
    printf("addAccount1\n");
    if (*head == NULL)
    {
        printf("addAccount1-1\n");
        (*head) = new1;
    }
    else
    {
        printf("addAccount1-2\n");
        while (current->next != NULL){
            printf("addAccount1-2-1\n");
            current = current->next;
            printf("addAccount1-2-2\n");
        }
        printf("addAccount1-2-3\n");
        current->next = new1;
    }
    printf("addAccount1-3\n");
}

void splitAccountFromFile(char *input, char *username, char *password, char *accountStatus, char *score)
{
	int usernameLength = 0;
	int passwordLength = 0;
	int accountStatusLength = 0;
	int scoreLength = 0;
	int i;
	printf("splitAccountFromFile\n");
	//split username
	for (i = 0; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		username[usernameLength++] = input[i];
	}
	i++;
	username[usernameLength] = '\0';

	//split password
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		password[passwordLength++] = input[i];
	}
	i++;
	password[passwordLength] = '\0';

	//split account
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		accountStatus[accountStatusLength++] = input[i];
	}
	i++;
	accountStatus[accountStatusLength] = '\0';
	//split score
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '\n')
			break;
		score[scoreLength++] = input[i];
	}
	score[scoreLength] = '\0';
}

void readAccountFromFile(Account **head)
{
    FILE *fin;
    fin = fopen("account.txt", "r");
    char input[BUFF_SIZE];
    char username[30];
    char password[30];
    /*int position; // 0: admin (1 admin) 1: player (>1 player)
    int status;  //1 online  0 offline
    int accountStatus; //1: active     0: blocked
    int score;
    int maxScore;*/
    char position[5];
    char status[5];
    char accountStatus[5];
    char score[BUFF_SIZE];
    char maxScore[BUFF_SIZE];
    printf("readAccountFromFile\n");
    while (1)
    {
        if (feof(fin))
            break;
        fgets(input, BUFF_SIZE, fin);
        splitAccountFromFile(input, username, password, accountStatus, maxScore);
        printf("readAccountFromFile\n");
        addAccount(head, username, password, accountStatus, maxScore);
        printf("addAccount2\n");
    }
    fclose(fin);
}

//printf all account
void printListAccount(Account **head)
{
    printf("printListAccount\n");
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        //printf("STT: %d\n", ptr->position);
        printf("Username: %s\n", ptr->username);
        printf("Pass: %s\n", ptr->password);
        printf("Max Score: %d\n", ptr->maxScore);
        //printf("Account: %s\n", ptr->accountStatus == ACTIVE ? "Active" : "Blocked");
        //printf("Status : %s\n", ptr->status == ONLINE ? "Online" : "Offline");
        //printf("Count wrong password: %d\n", ptr->countSignIn);
        printf("\n");
    }
}

void blockAccount(Account **head, char *username)
{
    Account *ptr = findUserNameAccount(head, username);
    ptr->accountStatus = BLOCKED;
}
void signinAccount(Account **head, char *username)
{
    Account *ptr = findUserNameAccount(head, username);
    ptr->status = ONLINE;
}
