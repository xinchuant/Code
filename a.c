#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short unsigned_decimal_binary(char code[], int start, int end);

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
        if(line == 0)
        {
            unsigned short start_address = unsigned_decimal_binary(code[line], 0, 15);
            printf("x%04hX\n", start_address);
        }
        if(code[line][0] == EOF)
            break;
        line++;
    }
    unsigned short start_address = unsigned_decimal_binary(code[line],0,15);

}
unsigned short unsigned_decimal_binary(char code[], int start, int end)
{
    unsigned short a = 1;
    unsigned short ret = 0;
    int point = end;
    while (point >= start)
    {
        if(code[point] == '1')
            ret += a;
        a *= 2;
        point--;
    }
    return ret;
}