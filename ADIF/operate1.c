#include<stdio.h>
#include<string.h>

typedef struct record
{
    char qso_date[10];
    char time_on[7];
    char freq[11];
    char mode[6];
    char call[16];
    char rst_rcvd[4];
    char rst_sent[4];
}rec;


FILE *findEOH(FILE *fp);
int filetype(char *argv[]);
FILE *findnext(FILE *fp);
FILE *readADI(FILE *fp);


int main (int argc,char *argv[])
{
    // input
    if(!strcmp(argv[1],"-i"))
    {
        int type = filetype(argv);
        switch (type)
        {
            // adi
            case 0:
                FILE *fp = fopen(argv[2], "r");
                // 找到<EOH>
                fp = findEOH(fp);
                // 读取数据并存储
                fp = readADI(fp);
                fclose(fp);
                break;

            // csv
            case 1:

                break;
        }
    }

    // export
    else if (!strcmp(argv[1], "-o"))
    {
        int i = 0;
        for (; argv[2][i] != '.'; i++)
            ;
        if (argv[2][i + 1] == 'a') // adi
        {

        }
        else // csv
        {

        }
    }

    // search
    else if (!strcmp(argv[1], "-s"))
    {
        
    }

    // time period
    else if (!strcmp(argv[1], "-l"))
    {
        
    }

    // if command line argument is illegal
    else 
    {
        printf("Error:the argument \"%s\" is illegal.",argv[1]);
    }
    return 0;
}

FILE *findEOH(FILE *fp)
{
    char eoh[6];
    int eoh_judge = 0;
    for (; !eoh_judge;)
    {
        do
        {
            fscanf(fp, "%c", &eoh[0]);
        } while (eoh[0] != '<');
        fgets(&eoh[1], 5, fp);
        if (eoh[1] == 'e' || eoh[1] == 'E')
        {
            if (eoh[2] == 'o' || eoh[2] == 'O')
            {
                if (eoh[3] == 'h' || eoh[3] == 'H')
                {
                    if (eoh[4] == '>')
                    {
                        eoh_judge = 1;
                    }
                }
            }
        }
        if (!eoh_judge)
        {
            fseek(fp, -3, SEEK_CUR);
        }
    }
    return fp;
}
int filetype(char *argv[])
{
    int type = 0;
    int i = 0;
    while (argv[2][i]!='.')
    {
        i++;
    }
    if(argv[2][i+1]=='c')
    {
        type = 1;
    }
    return type;
}
FILE *findnext(FILE *fp) // 指针停在"<"的右边一个字符
{
    char temp;
    fscanf(fp, "%c", &temp);
    for (;temp!='<';)
    {
        fscanf(fp, "%c", &temp);
    }
    return fp;
} 
FILE *readADI(FILE *fp)
{
    while(!feof(fp))
    {
        rec list;
        char a[40];
        char b[20];
        while(!feof(fp))//循环结束时指针在EOR右边的">"
        {
            findnext(fp);
            int i = 0;
            char temp;
            int len;
            for (; i < 3; i++)
            {
                fscanf(fp, "%c",&a[i]);
            }
            if (a[0] == 'e' || a[0] == 'E')
            {
                if (a[1] == 'o' || a[1] == 'O')
                {
                    if (a[2] == 'r' || a[2] == 'R')
                    {
                        break;
                    }
                }
            }
            fscanf(fp, "%c", &temp);
            while (temp != ':')
            {
                a[i] = temp;
                i++;
                fscanf(fp, "%c", &temp);
            }
            a[i] = '\0';
            fscanf(fp, "%d", &len);
            fseek(fp, 1, SEEK_CUR);
            fgets(b, len + 1, fp);
            b[len] = '\0';
            // printf("%s\n", b);
            switch (strlen(a))
            {
            case 8:
                if(a[0]=='q'||a[0]=='Q')
                {
                    if(a[1]=='s'||a[1]=='S')
                    {
                        if(a[2]=='o'||a[2]=='O')
                        {
                            strcpy(list.qso_date, b);
                        }
                    }
                    
                }
                else if (a[0] == 'r' || a[0] == 'R')
                {
                    if (a[1] == 's' || a[1] == 'S')
                    {
                        if (a[2] == 't' || a[2] == 'T')
                        {
                            if(a[3]=='_')
                            {
                                if (a[4] == 'r' || a[4] == 'R')
                                {
                                    strcpy(list.rst_rcvd, b);
                                }
                                else if (a[4] == 's' || a[4] == 'S' )
                                {
                                    strcpy(list.rst_sent, b);
                                }
                                
                            }
                        }
                    }
                }
                    break;
            case 7:
                    if (a[0] == 't' || a[0] == 'T')
                    {
                        if (a[1] == 'i' || a[1] == 'I')
                        {
                            if (a[2] == 'm' || a[2] == 'M')
                            {
                                if(b[4]>'9'||b[4]<'0')
                                {
                                    b[4] = '0';
                                    b[5] = '0';
                                }
                                strcpy(list.time_on, b);
                            }
                        }
                    }
                    break;
            case 4:
                if (a[0] == 'f' || a[0] == 'F')
                {
                    strcpy(list.freq, b);
                }
                else if (a[0] == 'm' || a[0] == 'M')
                {
                    strcpy(list.mode, b);
                }
                else 
                {
                    strcpy(list.call, b);
                }
                break;
            default:
                break;
            }
            for (int j = 0; j < 20;j++)
            {
                b[j] = '0';
            }
            printf("%s\n", list.qso_date);
            printf("%s\n", list.time_on);
            printf("%s\n", list.freq);
            printf("%s\n", list.mode);
            printf("%s\n", list.call);
            printf("%s\n", list.rst_rcvd);
            printf("%s\n", list.rst_sent);

        } 
        
    }
    return fp;
}
