#include<stdio.h>
#include<ctype.h>
#include<string.h>

void maHoa(char *text, int key, char *result){
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
        // invalid character
        else {
            printf("Invalid Message\n");
        }
        // adding encoded answer 
        text[i] = ch;
    }
}

void giaiMa(char *text, int key, char *result){
    char ch;
    
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        // check for valid character
        
        if (isalnum(ch) || ch == ' ') {
            // lower case characters
            if (islower(ch)) {
                ch = (ch - 'a' - key) % 26 + 'a';
            }
            // uppercase characters
            if (isupper(ch)) {
                ch = (ch - 'A' - key) % 26 + 'A';
            }
            // numbers
            if (isdigit(ch)) {
                ch = (ch - '0' - key) % 10 + '0';
            }
        }
        // invalid character
        else {
            printf("Invalid Message\n");
        }
        // adding encoded answer 
        text[i] = ch;
    }
}

int main(){
    char text[500], ch, result[500];
    int key;

    // taking user input
    printf("Enter a message to encrypt: ");
    memset(text,'\0',(strlen(text)+1));
    fgets(text, 1000, stdin);
    text[strlen(text)-1]='\0';
    //scanf("%s", text);
    printf("Enter the key: ");
    scanf("%d", & key);

  // visiting character by character
    //maHoa(text,key,result);
    giaiMa(text,key,result);

    

  

  printf("Encrypted message: %s", text);

  return 0;
}
