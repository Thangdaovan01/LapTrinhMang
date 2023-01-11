#include<stdio.h>
#include<ctype.h>
#include<string.h>

void maHoa(FILE* input, FILE* output, int key) {
  char c;
  while ((c = fgetc(input)) != EOF) {
    if (c >= 'a' && c <= 'z') {
      c = c + key;
      if (c > 'z') {
        c = c - 'z' + 'a' - 1;
      }
    } else if (c >= 'A' && c <= 'Z') {
      c = c + key;
      if (c > 'Z') {
        c = c - 'Z' + 'A' - 1;
      }
    }
    fputc(c, output);
  }
}

void giaiMa(FILE* input, FILE* output, int key) {
  char c;
  while ((c = fgetc(input)) != EOF) {
    if (c >= 'a' && c <= 'z') {
      c = c - key;
      if (c < 'a') {
        c = c + 'z' - 'a' + 1;
      }
    } else if (c >= 'A' && c <= 'Z') {
      c = c - key;
      if (c < 'A') {
        c = c + 'Z' - 'A' + 1;
      }
    }
    fputc(c, output);
  }
}