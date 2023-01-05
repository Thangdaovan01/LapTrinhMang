#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int numberSignIn=0;
char userSignIn[30];
#define BUFF_SIZE 1024

typedef struct{
	char username[30];
	char password[10];
	int status;	
}Account;

typedef struct node{
	Account data;
	struct node *next;
}Node;



Node* createNode(Account acc){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->next = NULL; 
    temp->data = acc;  
    return temp;
}

Node* addEnd(Node* head, Account acc){
	Node *p=head;
	
	if(head==NULL){
		return createNode(acc);
	}
	while(p->next != NULL){
		p = p->next;
	}
		
	while(p->next != NULL)
		p = p->next;
	Node* q = createNode(acc);
	p->next = q;
	
	return head;	
}

void getFile(Node* head){
	FILE *p;
	Account acc[50];
	p=fopen("account.txt","r");
	if (p== NULL){
		printf("Cannot open %s.\n", "account.txt");
		//return;
    } 
	int i=0;
	while(fscanf(p,"%s %s %d\n",acc[i].username,acc[i].password,&acc[i].status) != EOF){
		head = addEnd(head,acc[i]);
		i++;
	}
	fclose(p);
}

void displayList(Node* head)
{
	Node* p=head;
  //if (head == NULL) return;
  
  while(p != NULL)
    {
      printf("%s %s %d \n",p->data.username, p->data.password, p->data.status);
      p = p->next;
    }
}

int checkUsername(Node *head, char *username){
	Node* p=head;
	while(p!=NULL){
		if(strcmp(p->data.username, username) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

int checkPassword(Node *head, char *password){
	Node* p=head;
	while(p!=NULL){
		if(strcmp(p->data.password, password) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

void printInFile(char* username, char* password){
	FILE *p;
	p = fopen("account.txt","a");
	fprintf(p,"\n%s %s 1", username, password);
	fclose(p);
}

int checkAccount(Node* head, char* username, char* password){
	Node* p=head;
	while(p!=NULL){
		if(strcmp(p->data.username, username) == 0 && strcmp(p->data.password, password) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

int checkStatus(Node *head, char* username){
	Node* p=head;
	while(p!=NULL){
		if(strcmp(p->data.username, username) == 0)
			if(p->data.status == 1){
				return 1;
			}else{
				return 0;
			}	
		p = p->next;
	}
}

void blockAccount(Node* head, char* username){
	
	Node* p = head;
	while(p != NULL){
		if(strcmp(p->data.username, username) == 0){
			p->data.status = 0;
			break;
		}
		p = p->next;
	}
	head = p;
}

void printAllAccount(Node* head){
	FILE *fp;
	fp = fopen("account.txt","w");
	while(head!=NULL){
		fprintf(fp,"%s %s %d\n",head->data.username, head->data.password, head->data.status);
		head = head->next;
	}
	fclose(fp);
}

int checkSignIn(char* username){
	if(strcmp(userSignIn,username) == 0)
		return 1;
	return 0;
}

void check_client(Node* head, char* username, char* password){
    Node* p=head;
    int count = 0;
    char recv_data3[BUFF_SIZE];
    if(checkUsername(p,username) == 0){
		//printf("Cannot find account\n");
        strcpy(recv_data3, "Cannot find account");
        
	}else{
        if(checkStatus(p, username) == 0){
			//printf("Account is blocked or inactive\n");
            strcpy(recv_data3, "Account is blocked or inactive");
		}else{
            do{
				if(checkAccount(p,username,password) == 0){
					//printf("Password is incorrect. Please try again\n");
                    strcpy(recv_data3, "Password is incorrect. Please try again");
					count++;
					//printf("%d\n",count);
				}else{
					//printf("Login is successful!");
                    strcpy(recv_data3, "Login is successful!");
					break;
				}
			}while(count<3);
			//displayList(head);
			if(count == 3){
				blockAccount(p,username);
				//printAllAccount(p);
				//printf("Password is incorrect. Account is blocked\n");
                strcpy(recv_data3, "Password is incorrect. Account is blocked");
			}
        }
    }
}