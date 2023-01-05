#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int numberSignIn=0;
char userSignIn[30];

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

int main(){
	Node* head = NULL;
	Account acc[50], acc1;
	char user_name[30], pass[10];
	int n,i=0,count=0;

	FILE *p;
	p=fopen("account.txt","r");
	if (p== NULL){
		printf("Cannot open %s.\n", "account.txt");
		//return;
    } 
	
	while(fscanf(p,"%s %s %d\n",acc[i].username,acc[i].password,&acc[i].status) != EOF){
		head = addEnd(head,acc[i]);
		i++;
	}
		
	
	int menu;
	char username1[30], password1[10];
	do{
		printf("U1SER MANAGEMENT PROGRAM\n----------------------------------- \n1. Register\n2. Sign in \n3. Search\n4. Sign out\nYour choice (1-4, other to quit): ");
		
		scanf("%d",&menu);
		switch(menu){
			case 1:
				//displayList(head);
				printf("Nhap username: ");
				scanf("%s",user_name);
				if(checkUsername(head,user_name) == 1){
					printf("Account existed\n");
				}else{
					printf("Nhap Password: ");
					scanf("%s",pass);
					printInFile(user_name, pass);
					strcpy(acc1.username,user_name);
					strcpy(acc1.password,pass);
					acc1.status = 1;
					addEnd(head,acc1);
					printf("Successful registration\n");
				}
				
				break;
			case 2:
				printf("SIGN IN\n");
				printf("Nhap username: ");
				scanf("%s",user_name);
				if(checkUsername(head,user_name) == 0){
					printf("Cannot find account\n");
				}else{
					if(checkStatus(head, user_name) == 0){
						printf("Account is blocked\n");
					}else{
						do{
							printf("Nhap Password: ");
							scanf("%s",pass);
							if(checkAccount(head,user_name,pass) == 0){
								printf("Password is incorrect\n");
								count++;
								//printf("%d\n",count);
							}else{
								printf("Hello %s\n",user_name);
								strcpy(userSignIn,user_name);
								numberSignIn += 1;
								break;
							}
						}while(count<3);
						//displayList(head);
						if(count == 3){
							blockAccount(head,user_name);
							printAllAccount(head);
							printf("Password is incorrect. Account is blocked\n");
						}
						//displayList(head);
					}
				}
				break;
			case 3:
				printf("Nhap username: ");
				scanf("%s",user_name);
				if(checkUsername(head,user_name) == 0){
					printf("Cannot find account\n");
				}else{
					if(numberSignIn == 0){
						printf("Account is not sign in\n");
					}else{
						if(checkStatus(head, user_name)==0){
							printf("Account is blocked\n");
						}else{
							printf("Account is active\n");
						}
					}
				}
				break;
			case 4:
				printf("Nhap username: ");
				scanf("%s",user_name);
				if(checkUsername(head,user_name) == 0){
					printf("Cannot find account\n");
				}else{
					if(checkSignIn(user_name) == 0){
						printf("Account is not sign in\n");
					}else{
						printf("Goodbye %s\n",user_name);
						numberSignIn = 0;
					}
				}
				break;
			
			case 6:
				displayList(head);
				break;
			default:
				return 0;
				break;
		}
	}while(1);

	fclose(p);
}


