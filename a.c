#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short R0 = 0x7777;
unsigned short R1 = 0x7777;
unsigned short R2 = 0x7777;
unsigned short R3 = 0x7777;
unsigned short R4 = 0x7777;
unsigned short R5 = 0x7777;
unsigned short R6 = 0x7777;
unsigned short R7 = 0x7777;

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
    unsigned short start_address;

}