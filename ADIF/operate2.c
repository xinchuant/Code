#include <stdio.h>
#include <string.h>

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

void stringup(char a[]);
int filetype(char *argv[]);
FILE *findEOH(FILE *fp);
FILE *readADI(FILE *fp);

int main(int argc, char *argv[])
{
    // input
    if (!strcmp(argv[1], "-i"))
    {
        int type = filetype(argv);
        if(type) //csv
        {

        }
        else //adi
        {
            FILE *fp = fopen(argv[2], "r");
            // 找到<EOH>
            fp = findEOH(fp);
            // 读取数据并存储
            fp = readADI(fp);
            fclose(fp);
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
        printf("Error:the argument \"%s\" is illegal.", argv[1]);
    }
    return 0;
}
int filetype(char *argv[])
{
    int type = 0;
    int i = 0;
    while (argv[2][i] != '.')
    {
        i++;
    }
    if (argv[2][i + 1] == 'c')
    {
        type = 1;
    }
    return type;
}
void stringup(char a[])
{
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] >= 'a' && a[i] <= 'z')
        {
            a[i] = a[i] + 'A' - 'a';
        }
    }
}
FILE *findEOH(FILE *fp)//返回的文件指针指向">"后面一个字符
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
FILE *readADI(FILE *fp)
{
    while (!feof(fp))
    {
        do
        {
            
        } while ();
        
        
    }
    return fp;
}
FILE *