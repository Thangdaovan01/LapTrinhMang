#include<stdio.h>
#include<ctype.h>
#include<string.h>

void maHoaFile(FILE* input, FILE* output, int key) {
  char ch;
  while ((ch = fgetc(input)) != EOF) {
    if (isalnum(ch) || ch == ' ') {
      // lower case characters
      if (islower(ch)) {
        ch = (ch - 'a' + key) % 26 + 'a';
      }
      // uppercase characters
      if (isupper(ch)) {
        ch = (ch - 'A' + key) % 26 + 'A';
      }
      // numbers
      if (isdigit(ch)) {
        ch = (ch - '0' + key) % 10 + '0';
      }
    }
    fputc(ch, output);
  }
}

void giaiMaFile(FILE* input, FILE* output, int key) {
  char ch;
  while ((ch = fgetc(input)) != EOF) {
    if (isalnum(ch) || ch == ' ') {
      // lower case characters
      if (islower(ch)) {
        ch = (ch - 'a' - key + 26) % 26 + 'a';
      }
      // uppercase characters
      if (isupper(ch)) {
        ch = (ch - 'A' - key +26) % 26 + 'A';
      }
      // numbers
      if (isdigit(ch)) {
        ch = (ch - '0' - key + 26) % 10 + '0';
      }
    }
    fputc(ch, output);
  }
}

void maHoaText(char *text, int key){
    char ch;
    
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        // check for valid character
        
        if (isalnum(ch) || ch == ' ') {
            // lower case characters
            if (islower(ch)) {
                ch = (ch - 'a' + key) % 26 + 'a';
            }
            // uppercase characters
            if (isupper(ch)) {
                ch = (ch - 'A' + key) % 26 + 'A';
            }
            // numbers
            if (isdigit(ch)) {
                ch = (ch - '0' + key) % 10 + '0';
            }
        }
        
        text[i] = ch;
    }
}

void giaiMaText(char *text, int key){
    char ch;
    
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        // check for valid character
        
        if (isalnum(ch) || ch == ' ') {
            // lower case characters
            if (islower(ch)) {
                ch = (ch - 'a' - key + 26) % 26 + 'a';
            }
            // uppercase characters
            if (isupper(ch)) {
                ch = (ch - 'A' - key + 26) % 26 + 'A';
            }
            // numbers
            if (isdigit(ch)) {
                ch = (ch - '0' - key + 26) % 10 + '0';
            }
        }
         
        text[i] = ch;
    }
}