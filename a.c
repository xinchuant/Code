#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short unsigned_binary_to_decimal(char code[], int start, int end);
short signed_binary_to_decimal(char code[], int start, int end);

unsigned short R[8] = {0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777, 0x7777};
int condition_code = 0;
int halt = 0;
char code[10000][16];
char start_address_bin[16];

int main()
{
    scanf("%s", start_address_bin);
    unsigned short start_address = unsigned_binary_to_decimal(start_address_bin, 0, 15);
    for (int line = 0; 1; line++)
    {
        scanf("%s", code[line]);
        if (code[line][0] == EOF)
            break;
        if (code[line][0] == '&') // 用于测试者结束输入指令
            break;
    }
    for (int line = 0; !halt;line++)
    {

    }
    for (int i = 0; i < 8; i++)
    {
        printf("R%d = x%04hX\n", i, R[i]);
    }
}

unsigned short unsigned_binary_to_decimal(char code[], int start, int end)
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

short signed_binary_to_decimal(char code[], int start, int end)
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
    ret = flag * unsigned_binary_to_decimal(code_copy, start, end);
    return ret;
}

