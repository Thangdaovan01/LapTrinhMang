#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int numberSignIn=0;
char userSignIn[30];
#define BUFF_SIZE 1024

typedef struct{
	char filename[30];
	char filepath[100];
}Image;

typedef struct node{
	Image data;
	struct node *next;
}Node;

/*typedef struct node{
	char* data;
	struct node *next;
}Node1;*/

Node* createNode(Image img){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->next = NULL; 
    temp->data = img;  
    return temp;
}

Node* addEnd(Node* head, Image img){
	Node *p=head;
	
	if(head==NULL){
		return createNode(img);
	}
	while(p->next != NULL){
		p = p->next;
	}
		
	while(p->next != NULL)
		p = p->next;
	Node* q = createNode(img);
	p->next = q;
	
	return head;	
}




/*
Node* createNode1(char* name){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->next = NULL; 
    temp->data = name;  
    return temp;
}

Node* addEnd1(Node* head, char* name){
	Node *p=head;
	
	if(head==NULL){
		return createNode(name);
	}
	while(p->next != NULL){
		p = p->next;
	}
		
	while(p->next != NULL)
		p = p->next;
	Node* q = createNode(name);
	p->next = q;
	
	return head;	
}
*/
void getFile(Node* head){
	FILE *p;
	Image img[50];
	p=fopen("image1.txt","r");
	if (p== NULL){
		printf("Cannot open %s.\n", "image1.txt");
		//return;
    } 
	int i=0;
	while(fscanf(p,"%s %s\n",img[i].filename,img[i].filepath) != EOF){
		head = addEnd(head,img[i]);
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
      printf("%s %s\n",p->data.filename, p->data.filepath);
      p = p->next;
    }
}

void displayList1(Node* head)
{
	Node* p=head;
  //if (head == NULL) return;
  
  while(p != NULL)
    {
      printf("%s\n",p->data.filename);
      p = p->next;
    }
}

int checkFilename(Node *head, char *file_name){
	Node* p=head;
	while(p!=NULL){
		if(strcmp(p->data.filename, file_name) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

int checkFilenameFormat(char *file_name){
	char a[100] ;
	//strcpy(a,strrev(file_name));
	int n=strlen(file_name);
	for(int i=n-1; i>=0; i--){
		a[n-1-i]=file_name[i];
	}
	a[n-1]='\0';
	//printf("\n%s\n",a);
	if(strncmp(a,"gnp",3)==0 || strncmp(a,"bmp",3)==0 || strncmp(a,"gpj",3)==0){
		return 1;
	}
	return 0;
}
