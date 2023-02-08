#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "question.h"
typedef enum
{
    USER,
    PASS,
    REGISTER,
    LOGOUT,
    CHECK,
    CHOOSE_ANWSER,
    TOPIC_LEVEL,
    HELP,
    INFORMATION,
} OPCODE;

typedef enum
{
    NOT_LOGGED_IN,
    UNAUTHENTICATE,
    AUTHENTICATED,
} PHASE;

typedef enum
{
    SYNTAX_ERROR = 02,
    INVALID_OPERATION = 03,
    USER_IS_NOT_SIGNIN = 04,
    GAME_IS_PLAYING_DONT_LOG_IN = 05,

    USER_NAME_FOUND = 11,
    USER_NAME_NOT_FOUND = 12,
    USER_NAME_BLOCKED = 13,
    USER_NAME_IS_SIGNIN = 14,

    PASSWORD_CORRECT = 21,
    PASSWORD_INCORRECT = 22,
    PASSWORD_INCORRECT_THREE_TIMES = 23,
    PASSWORD_CORRECT_BUT_ACCOUNT_IS_SIGNINED_IN_ORTHER_CLIENT = 24,

    LOGOUT_SUCCESS = 31,

    REGISTER_SUCCESSFULL = 41,
    REGISTER_USERNAME_EXISTED = 42,

    ANSWER_IS_CORRECT = 51,
    ANSWER_IS_INCORRECT = 52,
    ANSWER_IS_INVALID = 53,

    USER_USED_HINT_SUCCESS = 61,
    USER_USED_HINT_FAIL = 62,

    TOPIC_USER_CHOOSE_LEVEL = 71,
    TOPIC_TYPE_INVALID = 72,
    TOPIC_USER_DONT_CHOOSE_LEVEL = 73,

    INFORMATION_SUCCESS = 81,
    INFORMATION_ORTHER_PLAYER_ANSWERING = 82,

    GAME_READY = 91,
    GAME_NOT_READY = 92,
    GAME_END_WIN = 93,

} MESSAGE_STATUS;

typedef struct
{
    OPCODE code;
    char message[50];
} Request;

typedef struct
{
    //GAMEPLAY_STATUS status;
    MESSAGE_STATUS code;
    char message[50];
    char data[50];
} Response;
//core function
/*int receiveRequest(int socket, Request *buff, int size, int flags);
int sendRequest(int socket, Request *buff, int size, int flags);

int sendMessage(int socket, Response *msg, int size, int flags);
int receiveMessage(int socket, Response *msg, int size, int flags);

// set message response
void setMessageResponse(Response *msg);
void readMessageResponse(Response *msg);

//set opcode request
void setOpcodeRequest(Request *request, char *input);

//send question
int sendQuestion(int socket, Question *question, int size, int flags);
int receiveQuestion(int socket, Question *question, int size, int flags);
//send information
int sendInformation(int socket, Information *infor, int size, int flags);
int receiveInformation(int socket, Information *infor, int size, int flags);
//request get
void requestGet(int socket);
void requestLogout(int socket, char *username);
void requestCheckInformation(int socket);
void requestGetHelp(int socket);
#endif
*/

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
  if (msg->code != NULL)
  {
    switch (msg->code)
    {
    case SYNTAX_ERROR:
      strcpy(msg->message, "Syntax error ");
      break;
    case INVALID_OPERATION:
      strcpy(msg->message, "Invalid operation ");
      break;
    case USER_NAME_FOUND:
      strcpy(msg->message, "Username is correct ");
      break;
    case USER_NAME_NOT_FOUND:
      strcpy(msg->message, "Cannot find account ");
      break;
    case USER_NAME_BLOCKED:
      strcpy(msg->message, "Account is blocked ");
      break;
    case USER_NAME_IS_SIGNIN:
      strcpy(msg->message, "Login only one account ");
      break;
    case PASSWORD_CORRECT:
      strcpy(msg->message, "Login successful ");
      break;
    case PASSWORD_INCORRECT:
      strcpy(msg->message, "Password incorrect ");
      break;
    case PASSWORD_INCORRECT_THREE_TIMES:
      strcpy(msg->message, "Password is incorrect. Account is blocked ");
      break;
    case LOGOUT_SUCCESS:
      strcpy(msg->message, "Logout successful ");
      break;
    case REGISTER_SUCCESSFULL:
      strcpy(msg->message, "Register successfull ");
      break;
    case REGISTER_USERNAME_EXISTED:
      strcpy(msg->message, "Username is existed ");
      break;
    case PASSWORD_CORRECT_BUT_ACCOUNT_IS_SIGNINED_IN_ORTHER_CLIENT:
      strcpy(msg->message, "Account is signin in orhter client ");
      break;
    case ANSWER_IS_CORRECT:
      strcpy(msg->message, "The answer is correct ");
      break;
    case ANSWER_IS_INCORRECT:
      strcpy(msg->message, "The answer is incorrect \nEnd game");
      break;
    case ANSWER_IS_INVALID:
      strcpy(msg->message, "The answer is invalid ");
      break;
    case USER_USED_HINT_SUCCESS:
      strcpy(msg->message, "User used hint success! ");
      break;
    case USER_USED_HINT_FAIL:
      strcpy(msg->message, "User used hint fail! You have used up the suggestions ");
      break;
    case TOPIC_USER_CHOOSE_LEVEL:
      strcpy(msg->message, "");
      break;
    case TOPIC_TYPE_INVALID:
      strcpy(msg->message, "User choose level is invalid ");
      break;
    case INFORMATION_SUCCESS:
      strcpy(msg->message, "");
      break;
    case INFORMATION_ORTHER_PLAYER_ANSWERING:
      strcpy(msg->message, "");
      break;
    case GAME_READY:
      strcpy(msg->message, "Game ready ");
      break;
    case GAME_NOT_READY:
      strcpy(msg->message, "Waiting orther player... ");
      break;
    case TOPIC_USER_DONT_CHOOSE_LEVEL:
      strcpy(msg->message, "");
      break;
    case GAME_END_WIN:
      strcpy(msg->message, "End game.\nYou are champion ");
      break;
    case GAME_IS_PLAYING_DONT_LOG_IN:
      strcpy(msg->message, "\nGame is playing!! You can't login \n");
      break;
    default:
      strcpy(msg->message, "Exception ");
      break;
    }
  }
}

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