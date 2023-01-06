#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UserManagement.h"
#include "Student.h"

int login = 0;
char* fileName;
struct Student* students = NULL;
struct user currentUser;

void Menu()
{
	printf("\n");
	printf("USER MANAGEMENT PROGRAM\n");
	printf("--------------------------------------\n");
	printf("1. Register\n");
	printf("2. Activate\n");
	printf("3. Sign in\n");
	printf("4. Search\n");
	printf("5. Change password\n");
	printf("6. Sign out\n");
	printf("Your choice (1-6, other to quit)\n\n");
}

int convertString(char* num)
{
	int sum = 0;
	for (int i = 0; i < strlen(num); ++i)
	{
		sum *= 10;
		sum += num[i] - '0';
	}

	return sum;
}

int findUsername(struct Student* sL, char* username)
{
	while(sL != NULL)
	{
		if(strcmp(sL -> user, username) == 0)
			return 1;

		sL = sL -> next;
	}

	return 0;
}

void Register()
{
	printf("Register\n\n");
	char* username = (char*)calloc(100, sizeof(char));
	char* password = (char*)calloc(100, sizeof(char));

	printf("Username: ");
	scanf("%s", username);

	if(findUsername(students, username))
		printf("Account existed\n");
	else{
		printf("Password: ");
		scanf("%s", password);
		//add into list
		addStudent(username, password, 2, &students);
		printf("Successful registration. Activated required\n");
	}

	free(username);
	free(password);
}

void Activate()
{
	printf("Activate\n\n");
	char* username = (char*)calloc(100, sizeof(char));
	char* password = (char*)calloc(100, sizeof(char));
	char* _activate_code = (char*)calloc(100, sizeof(char));

	printf("Username: ");
	scanf("%s", username);
	printf("Password: ");
	scanf("%s", password);
	printf("Activate code: ");
	scanf("%s", _activate_code);

	struct Student* res = studentGet(username, password, &students);

	if(res == NULL)
	{
		printf("Username or password is not correct\n");
	}else{
		if(res -> state == 2)
		{
			if(strcmp(_activate_code, activate_code) == 0)
			{
				res -> state = 1;
				printf("Account is activated\n");
				res -> block = 0;
			}else{
				res -> block += 1;
				if(res -> block == 4)
				{	
					printf("Acitvation code is incorrect\n");
					printf("Account is blocked\n");
					res -> state = 0;
				}else{
					printf("Account is not activated\n");
				}
			}
		}else{
			if(res -> state == 1)
			{
				printf("Account is already activated\n");
			}else{
				printf("Account is blocked\n");
			}
		}
	}

	free(username);
	free(password);
}

void SignIn()
{
	if(login == 1)
	{
		printf("User already signed in\n");
		return;
	}
	printf("Sign in\n\n");
	char* username = (char*)calloc(100, sizeof(char));
	char* password = (char*)calloc(100, sizeof(char));
	printf("Username: ");
	scanf("%s", username);

	int res = checkStudent(username, students);
	struct Student* res2 = studentGetByName(username, &students);

	switch(res)
	{
		case 1:
		{
			printf("Password: ");
			scanf("%s", password);

			if(strcmp(password, res2 -> password) != 0)
			{
				printf("Password is incorrect\n");
				res2 -> block += 1;
				if(res2 -> block == 4)
				{
					res2 -> state = 0;
					printf("Account is blocked\n");
				}

				break;
			}

			switch(res2 -> state)
			{
				case 0:
				{
					printf("Account is blocked\n");
					break;
				}

				case 1:
				{
					printf("Hello %s\n", username);
					res2 -> block = 0;
					login = 1;
					currentUser.username = (char*)calloc(strlen(username), sizeof(char));
					currentUser.password = (char*)calloc(strlen(password), sizeof(char));

					strcpy(currentUser.username, username);
					strcpy(currentUser.password, password);
					break;
				}

				case 2:
				{
					printf("Account is not activated\n");
					break;
				}
			}
			break;
		}

		case 2:
		{
			printf("Password is incorrect\n");
			res2 -> block += 1;
			if(res2 -> block == 4)
			{
				res2 -> state = 0;
				printf("Account is blocked\n");
			}

			break;
		}

		case 0:
		{
			printf("Cannot find account\n");
			break;
		}
	}

	free(username);
	free(password);
}

void Search()
{
	printf("Search\n\n");
	char* username = (char*)calloc(100, sizeof(char));
	printf("Username: ");
	scanf("%s", username);
	struct Student* res = studentGetByName(username, &students);

	if(res != NULL)
	{
		switch(res -> state)
		{
			case 0:
			{
				printf("Account is blocked\n");
				break;
			}

			case 1:
			{
				printf("Account is active");
				break;
			}

			case 2:
			{
				printf("Account is not activated\n");
				break;
			}
		}
	}else{
		printf("Cannot find account\n");
	}

	free(username);
}

void ChangePassword()
{
	printf("Change password\n\n");
	char* username = (char*)calloc(100, sizeof(char));
	char* password = (char*)calloc(100, sizeof(char));
	char* newPassword = (char*)calloc(100, sizeof(char));
	printf("Username: ");
	scanf("%s", username);
	printf("Password: ");
	scanf("%s", password);
	printf("New password: ");
	scanf("%s", newPassword);

	if(!login)
	{
		printf("Account is not sign in\n");	
	}else{
		if(login && strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0)
		{
			struct Student* res = studentGetByName(username, &students);
			strcpy(res -> password, newPassword);
			printf("Password changed\n");
		}else{
			if(strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) != 0)
			{
				printf("Current password is incorrect. Please try again\n");
			}else{
				printf("Cannot find account\n");
			}
		}
	}

	free(username);
	free(password);
	free(newPassword);
}

void SignOut()
{
	printf("Sign out\n\n");
	char* username = (char*)calloc(100, sizeof(char));
	printf("Username: ");
	scanf("%s", username);

	if(!login)
	{
		printf("Account is not sign in\n");
	}else{
		struct Student* res = studentGetByName(username, &students);

		if(res != NULL)
		{
			printf("Good bye %s\n", username);
		}else{
			printf("Cannot find account\n");
		}
	}

	free(username);
}