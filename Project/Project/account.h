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
    int numHelp;
    int numTrueAns; //so cau tra loi dung
    int score;
    int maxScore; //so diem cao nhat
    struct account *next;
}Account;

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
Account *newAccount(char *username, char *password, char *position, char *maxScore)
{
    Account *new1 = (Account *)malloc(sizeof(Account));
    strcpy(new1->username, username);
    strcpy(new1->password, password);
    new1->status = OFFLINE;
    new1->position = atoi(position);
    new1->numTrueAns = 0;
    new1->numHelp = 0;
    new1->score = 0;
    new1->maxScore = atoi(maxScore);
    return new1;
}
//add node
void addAccount(Account **head, char *username, char *password, char *position,char *maxScore)
{
    Account *new1 = newAccount(username, password, position, maxScore);
    Account *current = (*head);
    if (*head == NULL)
    {
        (*head) = new1;
    }
    else
    {
        while (current->next != NULL){
            current = current->next;
        }
        current->next = new1;
    }
}

void splitAccountFromFile(char *input, char *username, char *password, char *position, char *score)
{
	int usernameLength = 0;
	int passwordLength = 0;
	int positionLength = 0;
	int scoreLength = 0;
	int i;
	//printf("splitAccountFromFile\n");
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
		position[positionLength++] = input[i];
	}
	i++;
	position[positionLength] = '\0';
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
    
    char position[5];
    char status[5];
    char numTrueAns[10];
    char score[BUFF_SIZE];
    char maxScore[BUFF_SIZE];
    //printf("readAccountFromFile\n");
    while (1)
    {
        if (feof(fin))
            break;
        fgets(input, BUFF_SIZE, fin);
        splitAccountFromFile(input, username, password, position, maxScore);
        addAccount(head, username, password, position, maxScore);
    }
    fclose(fin);
}

//printf all account
void printListAccount(Account **head)
{
    printf("printListAccount\n");
    *head = (*head)->next;
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        //printf("STT: %d\n", ptr->position);
        printf("Username: %s\n", ptr->username);
        printf("Pass: %s\n", ptr->password);
        printf("Max Score: %d\n", ptr->maxScore);
        printf("\n");
    }
}

void signinAccount(Account **head, char *username)
{
    Account *ptr = findUserNameAccount(head, username);
    ptr->status = ONLINE;
}

//kiem tra username (dung trong buoc dang nhap vs dang ky)
int checkUsername(Account *head, char *username)
{
    Account *p = head;
    int i;
    while(p!=NULL){
        if(strcmp(p->username, username)==0)
            return 5;
            //i=5;
        p=p->next; 
    }
    return 4;
}

//kiem tra vi tri la admin hay nguoi choi
int checkPosition(Account *head)
{
    Account *p = head;
    while(p!=NULL){
        if(p->position==0)
            return 1;
        p=p->next; 
    }
    return 0;
}


int checkAccount(Account *head, char *username, char *password)
{
    Account *p = head;
    int i = 0;
    if(checkUsername(p,username)!=5) return 2; //USERNAME_NOT_EXISTED 
    while(p!=NULL){
        if((checkUsername(p,username)==5) && (strcmp(p->password, password)==0))
            return 1;
        p=p->next;
    }
    return 3; //PASSWORD_INCORRECT 
}

void printInFile(char* username, char* password){
	FILE *p;
	p = fopen("account.txt","a");
	fprintf(p,"\n%s|%s|1|0", username, password);
	fclose(p);
}

int TinhTienThuong(Account *head)
{
    Account *p=head;
	int TienThuong = 0, SoCauTraLoiDung=0;
	if(p->numTrueAns==1)
        TienThuong = 200;
	if(p->numTrueAns == 2)
		TienThuong = 400;
	if(p->numTrueAns == 3)
		TienThuong = 600;
	if(p->numTrueAns == 4)
		TienThuong = 1000;
	if(p->numTrueAns == 5)
		TienThuong = 2000;
	if(p->numTrueAns == 6)
		TienThuong = 3000;
	if(p->numTrueAns == 7)
		TienThuong = 6000;
	if(p->numTrueAns == 8)
		TienThuong = 10000;
	if(p->numTrueAns == 9)
		TienThuong = 14000;
	if(p->numTrueAns == 10)
		TienThuong = 22000;
	if(p->numTrueAns == 11)
		TienThuong = 30000;
	if(p->numTrueAns == 12)
		TienThuong = 40000;
	if(p->numTrueAns == 13)
		TienThuong = 60000;
	if(p->numTrueAns == 14)
		TienThuong = 85000;
	if(p->numTrueAns == 15)
		TienThuong = 150000;
	return TienThuong;
}

int TinhTienThuong2(Account *head)
{
    Account *p=head;
	int TienThuong = 0, SoCauTraLoiDung=0;
	if(p->numTrueAns==1)
        TienThuong = 0;
	if(p->numTrueAns == 2)
		TienThuong = 0;
	if(p->numTrueAns == 3)
		TienThuong = 0;
	if(p->numTrueAns == 4)
		TienThuong = 0;
	if(p->numTrueAns == 5)
		TienThuong = 2000;
	if(p->numTrueAns == 6)
		TienThuong = 2000;
	if(p->numTrueAns == 7)
		TienThuong = 2000;
	if(p->numTrueAns == 8)
		TienThuong = 2000;
	if(p->numTrueAns == 9)
		TienThuong = 2000;
	if(p->numTrueAns == 10)
		TienThuong = 22000;
	if(p->numTrueAns == 11)
		TienThuong = 22000;
	if(p->numTrueAns == 12)
		TienThuong = 22000;
	if(p->numTrueAns == 13)
		TienThuong = 22000;
	if(p->numTrueAns == 14)
		TienThuong = 22000;
	if(p->numTrueAns == 15)
		TienThuong = 150000;
	return TienThuong;
}

//update lai khi co maxScore moi
void updateAccountList(Account *acc, int score){
    Account *account = (Account *)malloc(sizeof(Account));
    readAccountFromFile(&account);
    Account *ptr = NULL;
    FILE *p;
    p=fopen("account.txt","w");
    
    if(acc->maxScore < score){
        acc->maxScore = score;
    }
    fprintf(p,"%s|%s|%d|%d", acc->username, acc->password, acc->position, acc->maxScore);
    
    //in cac account con lai vao file
    for(ptr = account->next; ptr!= NULL; ptr = ptr->next){
        if(strcmp(ptr->username, acc->username)!=0){
            fprintf(p,"\n%s|%s|%d|%d", ptr->username, ptr->password, ptr->position, ptr->maxScore);
        } 
        
    }
    fclose(p);
}


void deleteAcc(Account **head, char *str)
{
    Account *tmp;
    Account *result = findUserNameAccount(head, str);
    Account *current;
    if (*head == result)
    {
        current = *head;
        *head = (*head)->next;
    }
    else
        for (tmp = *head; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->next == result)
            {
                current = tmp->next;
                tmp->next = current->next;
            }
        }
    free(current);
}

Account *findMaxScore(Account *account1){
    Account *acc = NULL;
    Account *acc1 = account1->next;
    for(acc = account1->next; acc!=NULL; acc=acc->next){
        if(acc->maxScore > acc1->maxScore){
            acc1 = acc;
        }
    }
    return acc1;
}

void xepHangTop10(){
    Account *account1 = (Account *)malloc(sizeof(Account));
    readAccountFromFile(&account1);
    Account *acc = NULL;
    FILE *p;
    p=fopen("xephang.txt","w");
    //printListAccount(&account1);
    int i=0;
    for(i=0; i<10; i++){
        acc = findMaxScore(account1);
        //printf("Username: %s\n", acc->username);
        //printf("Pass: %s\n", acc->password);
        //printf("Max Score: %d\n", acc->maxScore);
        fprintf(p,"%d|%s|%d\n",i+1, acc->username, acc->maxScore);
    
        deleteAcc(&account1, acc->username);
    } 
    fclose(p);
}