#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum
{
    LOGIN = 01,
    SIGNUP = 02,
    CHOOSE_ANWSER = 03,
    HELP = 04,
    SHOWRANKTABLE = 05,
} OPCODE;

typedef enum
{
    NOT_LOGGED_IN,
    UNAUTHENTICATE,
    AUTHENTICATED,
} PHASE;

typedef enum
{
    LOGIN_SUCCESS = 01,
    USERNAME_NOT_EXISTED = 02,
    PASSWORD_INCORRECT = 03,

    SIGNIN_SUCCESS = 04,
    USERNAME_EXISTED = 05,

    TRUE_ANSWER = 06,
    WRONG_ANSWER = 07,
    INVALID_ANSWER = 10,

    NO_MORE_HELP = 11,
    HELP_SUCCESS = 12,

} MESSAGE_STATUS;

typedef struct
{
    OPCODE code;
    char username[50];
    char pass[50];
    char answer[50];
} Request;

typedef struct 
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
} RequestQuestion;
typedef struct
{
    //GAMEPLAY_STATUS status;
    MESSAGE_STATUS code;
    char message[50];
    char data[50];
    //char position[5];
} Response;

int receiveRequest(int socket, Request *buff, int size, int flags)
{
  int n;

  n = recv(socket, buff, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

int sendRequest(int socket, Request *buff, int size, int flags)
{
  int n;

  n = send(socket, buff, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

int receiveRequestQuestion(int socket, RequestQuestion *buff, int size, int flags)
{
  int n;

  n = recv(socket, buff, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

int sendRequestQuestion(int socket, RequestQuestion *buff, int size, int flags)
{
  int n;

  n = send(socket, buff, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

int sendResponse(int socket, Response *msg, int size, int flags)
{
  int n;
  n = send(socket, msg, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

int receiveResponse(int socket, Response *msg, int size, int flags)
{
  int n;
  n = recv(socket, msg, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

void setMessageResponse(Response *msg)
{
  //if (msg->code != NULL)
  //{
    switch (msg->code)
    {
    case LOGIN_SUCCESS:
      strcpy(msg->message, "LOGIN SUCCESS");
      break;
    case USERNAME_NOT_EXISTED:
      strcpy(msg->message, "USERNAME NOT EXISTED");
      break;
    case PASSWORD_INCORRECT:
      strcpy(msg->message, "PASSWORD INCORRECT");
      break;
    case SIGNIN_SUCCESS:
      strcpy(msg->message, "SIGNIN SUCCESS");
      break;
    case USERNAME_EXISTED:
      strcpy(msg->message, "USERNAME EXISTED");
      break;
    case TRUE_ANSWER:
      strcpy(msg->message, "TRUE ANSWER");
      break;
    case WRONG_ANSWER:
      strcpy(msg->message, "WRONG ANSWER");
      break;
    case INVALID_ANSWER:
      strcpy(msg->message, "INVALID ANSWER");
      break;
    case NO_MORE_HELP:
      strcpy(msg->message, "NO MORE HELP");
      break;
    case HELP_SUCCESS:
      strcpy(msg->message, "HELP SUCCESS");
      break;
    default:
      strcpy(msg->message, "Exception ");
      break;
    }
  //}
}
/*
void readMessageResponse(Response *msg)
{
  if (msg->code != NULL)
  {
    printf("%s\n", msg->message);
    switch (msg->code)
    {
    case PASSWORD_CORRECT:
      printf("Hello %s\n", msg->data);
      break;
    case LOGOUT_SUCCESS:
      printf("Goodbye %s\n", msg->data);
      break;
    case TOPIC_USER_CHOOSE_LEVEL:
      printf("User choose level %s\n", msg->data);
      break;
    default:
      break;
    }
  }
}
*/
/*void setOpcodeRequest(Request *request, char *input)
{
  char code[BUFF_SIZE], data[BUFF_SIZE];
  splitMessage(input, code, data);
  strcpy(request->message, data);
  if (strcmp(code, "USER") == 0)
    request->code = USER;
  else if (strcmp(code, "PASS") == 0)
    request->code = PASS;
  else if (strcmp(code, "REGISTER") == 0)
    request->code = REGISTER;
  else if (strcmp(code, "LOGOUT") == 0)
    request->code = LOGOUT;
  else if (strcmp(code, "CHECK") == 0)
    request->code = CHECK;
  else if (strcmp(code, "INFORMATION") == 0)
    request->code = INFORMATION;
  else if (strcmp(code, "ANSWER") == 0)
    request->code = CHOOSE_ANWSER;
  else if (strcmp(code, "TOPIC") == 0)
    request->code = TOPIC_LEVEL;
  else if (strcmp(code, "HELP") == 0)
    request->code = HELP;
}
*/
/*
int sendQuestion(int socket, Question *question, int size, int flags)
{
  int n;
  n = send(socket, question, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}
int receiveQuestion(int socket, Question *question, int size, int flags)
{
  int n;
  n = recv(socket, question, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}

void requestGet(int socket)
{
  Request *request = (Request *)malloc(sizeof(Request));
  setOpcodeRequest(request, "CHECK check");
  sendRequest(socket, request, sizeof(Request), 0);
}
void requestCheckInformation(int socket)
{
  Request *request = (Request *)malloc(sizeof(Request));
  setOpcodeRequest(request, "INFORMATION information");
  sendRequest(socket, request, sizeof(Request), 0);
}
int sendInformation(int socket, Information *infor, int size, int flags)
{
  int n;
  n = send(socket, infor, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}
int receiveInformation(int socket, Information *infor, int size, int flags)
{
  int n;
  n = recv(socket, infor, size, flags);
  if (n < 0)
    perror("Error: ");
  return n;
}
void requestLogout(int socket, char *username)
{
  Request *request = (Request *)malloc(sizeof(Request));
  char buff[BUFF_SIZE];
  strcpy(buff, "LOGOUT ");
  strcat(buff, username);
  setOpcodeRequest(request, buff);
  sendRequest(socket, request, sizeof(Request), 0);
}
void requestGetHelp(int socket)
{
  Request *request = (Request *)malloc(sizeof(Request));
  setOpcodeRequest(request, "HELP help");
  sendRequest(socket, request, sizeof(Request), 0);
}
*/