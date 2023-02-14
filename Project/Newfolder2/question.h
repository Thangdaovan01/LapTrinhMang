#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFF_SIZE 1024

typedef struct question
{
    int stt;
    char question[BUFF_SIZE];
    char answer1[BUFF_SIZE];
    char answer2[BUFF_SIZE];
    char answer3[BUFF_SIZE];
    char answer4[BUFF_SIZE];
    //LEVEL level;
    char level[10];
    char true_ans[5];
    char wrong_ans1[5];
    char wrong_ans2[5];
    struct question *next;
}Question;

Question **createQuestionList()
{
    Question **head = (Question **)malloc(sizeof(Question *));
    *head = NULL;

    return head;
}
/*LIST_ANSWER convertListAnswer(char *input)
{
    if (strcmp(input, "A") == 0)
        return A;
    else if (strcmp(input, "B") == 0)
        return B;
    else if (strcmp(input, "C") == 0)
        return C;
    else if (strcmp(input, "D") == 0)
        return D;
}

LEVEL convertLevel(char *input)
{
    if (strcmp(input, "EASY") == 0)
        return EASY;
    else if (strcmp(input, "NORMAL") == 0)
        return NORMAL;
    else if (strcmp(input, "HARD") == 0)
        return HARD;
    else
        return OTHER;
}
*/
Question *newQuestion(char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue, char *answerWrong1, char *answerWrong2)
{
    Question *new1 = (Question *)malloc(sizeof(Question));
    new1->stt = atoi(stt);
    //new1->level = convertLevel(level);
    strcpy(new1->level, level);
    strcpy(new1->question, question);
    strcpy(new1->answer1, answer1);
    strcpy(new1->answer2, answer2);
    strcpy(new1->answer3, answer3);
    strcpy(new1->answer4, answer4);
    strcpy(new1->true_ans, answerTrue);
    strcpy(new1->wrong_ans1, answerWrong1);
    strcpy(new1->wrong_ans2, answerWrong2);
    return new1;
}

void addQuestion(Question **head, char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue, char *answerWrong1, char *answerWrong2)
{
    Question *new1 = newQuestion(stt, level, question, answer1, answer2, answer3, answer4, answerTrue, answerWrong1, answerWrong2);
    Question *current = (*head);
    if (*head == NULL)
    {
        (*head) = new1;
    }
    else
    {
        while (current->next != NULL)
            current = current->next;
            current->next = new1;
    }
}

void splitQuestionFromFile(char *input, char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue, char *answerWrong1, char *answerWrong2)
{
	int sttLength = 0;
	int levelLength = 0;
	int questionLength = 0;
	int answer1Length = 0;
	int answer2Length = 0;
	int answer3Length = 0;
	int answer4Length = 0;
	int answerTrueLength = 0;
    int answerWrong1Length = 0;
    int answerWrong2Length = 0;
	int i;
	//split stt
	for (i = 0; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		stt[sttLength++] = input[i];
	}
	i++;
	stt[sttLength] = '\0';

	//split level
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		level[levelLength++] = input[i];
	}
	i++;
	level[levelLength] = '\0';

	//split question
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		question[questionLength++] = input[i];
	}
	i++;
	question[questionLength] = '\0';

	//split answer1
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer1[answer1Length++] = input[i];
	}
	i++;
	answer1[answer1Length] = '\0';

	//split answer2
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer2[answer2Length++] = input[i];
	}
	i++;
	answer2[answer2Length] = '\0';

	//split answer3
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer3[answer3Length++] = input[i];
	}
	i++;
	answer3[answer3Length] = '\0';

	//split answer4
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer4[answer4Length++] = input[i];
	}
	i++;
	answer4[answer4Length] = '\0';

	//split answer true
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answerTrue[answerTrueLength++] = input[i];
	}
    i++;
	answerTrue[answerTrueLength] = '\0'; 

    //split answer wrong 1
    for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answerWrong1[answerWrong1Length++] = input[i];
	}
    i++;
	answerWrong1[answerWrong1Length] = '\0';

    //split answer wrong 2
    for (i; i < strlen(input); i++)
	{
		if (input[i] == '\n')
			break;
		answerWrong2[answerWrong2Length++] = input[i];
	}
	answerWrong2[answerWrong2Length] = '\0';
}

void readQuestionFromFile(Question **head)
{
    FILE *fin;
    fin = fopen("question.txt", "r");
    char input[BUFF_SIZE];
    char stt[BUFF_SIZE];
    char level[BUFF_SIZE];
    char question[BUFF_SIZE];
    char answer1[BUFF_SIZE];
    char answer2[BUFF_SIZE];
    char answer3[BUFF_SIZE];
    char answer4[BUFF_SIZE];
    char answerTrue[BUFF_SIZE];
    char answerWrong1[BUFF_SIZE];
    char answerWrong2[BUFF_SIZE];

    while (1)
    {
        if (feof(fin))
            break;
        fgets(input, BUFF_SIZE, fin);
        splitQuestionFromFile(input, stt, level, question, answer1, answer2, answer3, answer4, answerTrue, answerWrong1, answerWrong2);
        addQuestion(head, stt, level, question, answer1, answer2, answer3, answer4, answerTrue, answerWrong1, answerWrong2);
    }
    fclose(fin);
}

void printListQuestion(Question **head)
{
    Question *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        printf("\nStt: %d\n", ptr->stt);
        printf("Level: %s\n", ptr->level);
        printf("Question: %s\n", ptr->question);
        printf("A: %s\n", ptr->answer1);
        printf("B: %s\n", ptr->answer2);
        printf("C: %s\n", ptr->answer3);
        printf("D: %s\n", ptr->answer4);
        printf("True ans: %s\n", ptr->true_ans);
        printf("Wrong ans: %s %s\n", ptr->wrong_ans1, ptr->wrong_ans2);
    }
}

int searchQuestionByLevel(Question **head, /*LEVEL*/char* level, int *numberArray)
{
    Question *ptr;
    int i = 0;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->level == level)
            numberArray[i++] = ptr->stt;
    }
    return i;
}

Question *searchQuestionByStt(Question **head, int stt)
{
    Question *ptr;
    int i = 0;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->stt == stt)
            return ptr;
    }
    return NULL;
}

void deleteQuestion(Question **head, int stt)
{
    Question *tmp;
    Question *result = searchQuestionByStt(head, stt);
    Question *current;
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

int checkAnswer(char *node, char *ans)
{
    if (node == ans)
        return 1;
    else
        return 0;
}

void xuatMotCauHoi(Question *head)
{
    Question *p=head;
    printf("%s\nA. %s\nB. %s\nC. %s\nD. %s\n",p->question,p->answer1,p->answer2,p->answer3,p->answer4);  

    //printf("%s\nA. %s\nB. %s\nC. %s\nD. %s\nDap an dung %s\n",p->question,p->answer1,p->answer2,p->answer3,p->answer4,p->true_ans);  
}

Question *exportQuestion(Question *head, char *str)
{
    Question *p=head;
    if(strcmp(p->level, str)==0)
        return p;
        //printf("%s\nA. %s\nB. %s\nC. %s\nD. %s\n",p->question,p->answer1,p->answer2,p->answer3,p->answer4);  
}

void xuatMotDanhSachCauHoi(Question *head)
{
    Question *p=head;

    while(p!=NULL){
        //printf("%s\n%s\n%s\n%s\n%s\n",p->data.CauHoi,p->data.TraLoi.A,p->data.TraLoi.B,p->data.TraLoi.C,p->data.TraLoi.D);
        xuatMotCauHoi(p);
        p = p->next;
    }
}

int checkAnswer1(Question *head, char *answer)
{
    Question *ptr = head;
    //int i = 0;
    //for (ptr = head; ptr != NULL; ptr = ptr->next)
    //{
    //    printf("checkAnswer1-true answer: %s \n",ptr->true_ans);
    //    printf("checkAnswer1-answer: %s \n",answer);
        if (strcmp(ptr->true_ans,answer)==0)
            return 6;
   // }
    return 7;
}

int checkAnswer2(char *answer1){
    if((strcmp(answer1,"A")==0) || (strcmp(answer1,"B")==0) || (strcmp(answer1,"C")==0) || (strcmp(answer1,"D")==0) ||/* (strcmp(answer1,"H")==0) ||*/ (strcmp(answer1,"S")==0))
        return 1;
    return 0;
}

void quyen5050(Question *head){
    Question *ptr=head;
    printf("Dap an sai la %s va %s\n",ptr->wrong_ans1,ptr->wrong_ans2);
}

void menuQuyenTroGiup(){
    printf("\n\t\t\tMENU TRO GIUP");
  	printf("\n\tBam phim (1) de chon quyen tro giup 50:50\n");
    printf("\n\tBam phim (2) de chon quyen tro giup Goi dien thoai cho nguoi than\n");
    printf("\n\tBam phim (3) de chon quyen tro giup Xin y kien khan gia truong quay\n");
    printf("\n\tBam phim (4) de chon quyen tro giup Hoi to tu van o truong quay\n");
}

int receiveQuestion(int socket, Question *buff, int size, int flags)
{
  int n;

  n = recv(socket, buff, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

int sendQuestion(int socket, Question *buff, int size, int flags)
{
  int n;

  n = send(socket, buff, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

int checkInsertLevel(char *str){
    if((strcmp(str,"EASY")==0) || (strcmp(str,"NORMAL")==0) || (strcmp(str, "HARD")==0))
        return 1;
    return 0;
}

void insertQuestion1(char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *true_ans, char *wrong_ans1, char *wrong_ans2, char *level){
    printf("\nInsert question: ");
	memset(question,'\0',(strlen(question)+1));
	fgets(question, BUFF_SIZE, stdin);	
	question[strlen(question) - 1] = '\0';

    printf("\nInsert answer1: ");
	memset(answer1,'\0',(strlen(answer1)+1));
	fgets(answer1, BUFF_SIZE, stdin);	
	answer1[strlen(answer1) - 1] = '\0';

    printf("\nInsert answer2: ");
	memset(answer2,'\0',(strlen(answer2)+1));
	fgets(answer2, BUFF_SIZE, stdin);
	answer2[strlen(answer2) - 1] = '\0';

    printf("\nInsert answer3: ");
	memset(answer3,'\0',(strlen(answer3)+1));
	fgets(answer3, BUFF_SIZE, stdin);
	answer3[strlen(answer3) - 1] = '\0';

    printf("\nInsert answer4: ");
	memset(answer4,'\0',(strlen(answer4)+1));
	fgets(answer4, BUFF_SIZE, stdin);	
	answer4[strlen(answer4) - 1] = '\0';

    printf("\nInsert true_ans: ");
	memset(true_ans,'\0',(strlen(true_ans)+1));
	fgets(true_ans, BUFF_SIZE, stdin);	
	true_ans[strlen(true_ans) - 1] = '\0';

    printf("\nInsert wrong_ans1: ");
	memset(wrong_ans1,'\0',(strlen(wrong_ans1)+1));
	fgets(wrong_ans1, BUFF_SIZE, stdin);
	wrong_ans1[strlen(wrong_ans1) - 1] = '\0';

    printf("\nInsert wrong_ans2: ");
	memset(wrong_ans2,'\0',(strlen(wrong_ans2)+1));
	fgets(wrong_ans2, BUFF_SIZE, stdin);
	wrong_ans2[strlen(wrong_ans2) - 1] = '\0';

    do{
        printf("\nInsert level: ");
        memset(level,'\0',(strlen(level)+1));
        fgets(level, BUFF_SIZE, stdin);	
        level[strlen(level) - 1] = '\0';
    }while(checkInsertLevel(level)==0);

}

void printQuestionInFile(char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *true_ans, char *wrong_ans1, char *wrong_ans2, char *level){
	FILE *p;
	p = fopen("question.txt","a");
	fprintf(p,"\n1|%s|%s|%s|%s|%s|%s|%s|%s|%s", level, question, answer1, answer2, answer3, answer4, true_ans, wrong_ans1, wrong_ans2);
	fclose(p);
}

