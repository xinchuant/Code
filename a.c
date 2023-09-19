#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short unsigned_decimal_binary(char code[], int start, int end);
short signed_decimal_binary(char code[], int start, int end);

unsigned short R[8] = {0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777, 0x7777};

int main ()
{
    char code[10000][16];
    int line = 0;
    while (1)
    {
        scanf("%s", code[line]);
        if(code[line][0] == EOF)
            break;
        if(code[line][0] == '&')
            break;
        line++;
    }
    unsigned short start_address = unsigned_decimal_binary(code[line],0,15);
    for (int i = 0; i < 8;i++)
    {
        printf("R%d = x%04hX\n", i, R[i]);
    }
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

short signed_decimal_binary(char code[], int start, int end)
{
    short flag = 1;
    short ret = 0;
    // 复制字符串,防止更改原二进制码
    char code_copy[16];
    for (int i = 0; i < 16; i++)
    {
        code_copy[i] = code[i];
    }
    if (code_copy[start] == '1')
    {
        flag = -1;
        // 取反加一
        int point = start;
        while(point <= end)
        {
            if(code_copy[point] == '1')
                code_copy[point] = '0';
            else
                code_copy[point] = '1';
            point++;
        }
        int carry = 1;//将加的一视为第一位的carry
        point = end;
        while (point >= start)
        {
            if(carry)
            {
                if(code_copy[point] == '1')
                {
                    code_copy[point] = 0;
                    carry = 1;
                }
                else
                {
                    code_copy[point] = 1;
                    carry = 0;
                }
            }
            else
                break;//如果carry为0则后续carry均为0，直接结束即可
        }
    }
    ret = flag * unsigned_decimal_binary(code_copy, start, end);
    return ret;
}