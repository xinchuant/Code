#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main ()
{
    char code[10000][16];
    int line = 0;
    while (1)
    {
        scanf("%s", code[line]);
        printf("%s", code[line]);
        if(code[line][0] == EOF)
            break;
        line++;
    }
    
}