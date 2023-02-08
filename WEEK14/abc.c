#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkString(char *str, char *number, char *str1){
    char so[20];
    char chu[20];
    int len = strlen(str);
    int k=0, j=0;
    for(int i=0; i<len; i++){
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')){
            chu[k] = str[i];
            k++;
        }else if(str[i] >= '0' && str[i] <= '9'){
            so[j] = str[i];
            j++;
        }else return 0;
    }
    //printf("So: %s\nChu: %s\n", so, chu);
    chu[k]='\0';
    so[j]='\0';
    strcpy(number, so);
    strcpy(str1, chu);
    return 1;
}

int main(){
    char so[20];
    char chu[20];
    char str[50] = "abhG15adj";
    int m = checkString(str, so, chu);
    if(m==0) printf("Error\n");
    else {
        printf("Success!\n");
        printf("So: %s\nChu: %s\n", so, chu);
    }
    return 0;
}