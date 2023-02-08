//#include "../lib/question.h"
#include "question.h"
Question **createQuestionList()
{
    Question **head = (Question **)malloc(sizeof(Question *));
    *head = NULL;

    return head;
}
LIST_ANSWER convertListAnswer(char *input)
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

Question *newQuestion(char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue, char *answerWrong1, char *answerWrong2)
{
    Question *new = (Question *)malloc(sizeof(Question));
    new->stt = atoi(stt);
    new->level = convertLevel(level);
    strcpy(new->question, question);
    strcpy(new->answer1, answer1);
    strcpy(new->answer2, answer2);
    strcpy(new->answer3, answer3);
    strcpy(new->answer4, answer4);
    new->true_ans = convertListAnswer(answerTrue);
    new->wrong_ans1 = convertListAnswer(answerWrong1);
    new->wrong_ans2 = convertListAnswer(answerWrong2);
    return new;
}


void addQuestion(Question **head, char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue, char *answerWrong1, char *answerWrong2)
{
    Question *new = newQuestion(stt, level, question, answer1, answer2, answer3, answer4, answerTrue, answerWrong1, answerWrong2);
    Question *current = (*head);
    if (*head == NULL)
    {
        (*head) = new;
    }
    else
    {
        while (current->next != NULL)
            current = current->next;
        current->next = new;
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
		if (input[i] == '\n')
			break;
		answerTrue[answerTrueLength++] = input[i];
	}
	answerTrue[answerTrueLength] = '\0'; //int answerWrong1Length = 0;

    //split answer wrong 1
    for (i; i < strlen(input); i++)
	{
		if (input[i] == '\n')
			break;
		answerWrong1[answerWrong1Length++] = input[i];
	}
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
    fin = fopen("../data/question.txt", "r");
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
        printf("Stt: %d\n", ptr->stt);
        printf("Level: %d\n", ptr->level);
        printf("Question: %s\n", ptr->question);
        printf("A: %s\n", ptr->answer1);
        printf("B: %s\n", ptr->answer2);
        printf("C: %s\n", ptr->answer3);
        printf("D: %s\n", ptr->answer4);
        printf("True ans: %d\n", ptr->true_ans);
    }
}

int searchQuestionByLevel(Question **head, LEVEL level, int *numberArray)
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

/*Question *searchQuestionByStt(Question **head, int stt)
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
*/

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

int checkAnswer(LIST_ANSWER node, LIST_ANSWER ans)
{
    if (node == ans)
        return 1;
    else
        return 0;
}