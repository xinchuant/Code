#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct record
{
    char qso_date[10];
    char time_on[7];
    char freq[11];
    char mode[6];
    char call[16];
    char rst_rcvd[4];
    char rst_sent[4];
} rec;

int main()
{
     FILE *fp = fopen("store.bin", "rb");
    // write
    // rec *list = (rec *)malloc(sizeof(rec));
    // gets(list->qso_date);
    // gets(list->time_on);
    // gets(list->freq);
    // gets(list->mode);
    // gets(list->call);
    // gets(list->rst_rcvd);
    // gets(list->rst_sent);
    // fwrite(list, sizeof(rec), 1, fp);
    //read
     rec *list;
     fread(list,sizeof(rec),1,fp);
     printf("%s\n", list->qso_date);
     printf("%s\n", list->time_on);
     printf("%s\n", list->freq);
     printf("%s\n", list->mode);
     printf("%s\n", list->call);
     printf("%s\n", list->rst_rcvd);
     printf("%s\n", list->rst_sent);
     fclose(fp);
     return 0;
}