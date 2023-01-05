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
	p=fopen("taikhoan.txt","r");
	if (p== NULL){
		printf("Cannot open %s.\n", "account.txt");
		//return;
    } 
	int i=0;
	while(fscanf(p,"%s %s\n",acc[i].username,acc[i].password) != EOF){
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
      printf("%s %s\n",p->data.username, p->data.password);
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

void printInFile(char* username, char* mess){
	FILE *p;
	p = fopen("groupchat.txt","a");
	fprintf(p,"%s : %s", username, mess);
	fclose(p);
}

void readGroupchat(char *allmess){
	FILE *p;
	p = fopen("groupchat.txt","r");
	int i=0;
	char c;
	//fprintf(p,"%s : %s\n", username, mess);
	while ((c = fgetc(p)) != EOF)
    {
        allmess[i] = c;
        i++;
    }
    allmess[i]='\0';
    ///printf("String\n%s\n", allmess);
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
		fprintf(fp,"%s %s\n",head->data.username, head->data.password);
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