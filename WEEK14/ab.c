#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define SERVER_PORT  12345

#define TRUE             1
#define FALSE            0

typedef struct{
   char *number;
   char *str1;
}abc;

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

int hexstr2raw(char *in, void *out) {
    char c;
    uint32_t i = 0;
    uint8_t *b = (uint8_t*) out;
    while ((c = in[i]) != '\0') {
        uint8_t v;
        if (c >= '0' && c <= '9') {
            v = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            v = 10 + c - 'A';
        } else if (c >= 'a' || c <= 'f') {
            v = 10 + c - 'a';
        } else {
            return -1;
        }
        if (i%2 == 0) {
            b[i/2] = (v << 4);
            printf("c='%c' \t v='%u' \t b[i/2]='%u' \t i='%u'\n", c,v ,b[i/2], i);}
        else {
            b[i/2] |= v;
            printf("c='%c' \t v='%u' \t b[i/2]='%u' \t i='%u'\n", c,v ,b[i/2], i);}
        i++;
    }
    printf("OUT %s\n", out);
    return i;
}
int main (int argc, char *argv[])
{
   int    i, len, rc, on = 1, n;
   int    listen_sd, max_sd, new_sd;
   int    desc_ready, end_server = FALSE;
   int    close_conn;
   char   buffer[80], buff[80];
   struct sockaddr_in   addr;
   struct timeval       timeout;
   fd_set        master_set, working_set;
   ssize_t bytes_write;
   char number[30], str1[30];
   struct iovec iov[2];
   abc buff1;
    strcpy(number,"ber");
    strcpy(str1, "string");
    printf("%s\n", number);
   
                     iov[0].iov_base = number;
                     iov[0].iov_len = sizeof(number);
                     iov[1].iov_base = str1;
                     iov[1].iov_len = sizeof(str1);
    int j;
    i = hexstr2raw(number, iov[0].iov_base );
   return 0;
}