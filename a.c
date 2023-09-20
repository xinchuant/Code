#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short unsigned_binary_to_decimal(char c[], int start, int end);
short signed_binary_to_decimal(char c[], int start, int end);
void BR(char c[]);
void ADD(char c[]);
void LD(char c[],char b[],int line);
void ST(char c[]);
void JSR(char c[]);
void AND(char c[]);
void LDR(char c[]);
void STR(char c[]);
void NOT(char c[]);
void LDI(char c[]);
void STI(char c[]);
void JMP(char c[]);
void LEA(char c[]);
void TRAP_HALT_ONLY();

unsigned short R[8] = {0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777};
int condition_code = 0;
int halt = 0;

int main()
{
    char code[1000][16];
    char start_address_bin[16];
    //取得程序起始地址
    scanf("%s", start_address_bin);
    unsigned short start_address = unsigned_binary_to_decimal(start_address_bin, 0, 15);
    //取得指令
    for (int line = 0; 1; line++)
    {
        scanf("%s", code[line]);
        if (code[line][0] == EOF)
            break;
        if (code[line][0] == '&') // 用于测试者结束输入指令
            break;
    }
    // 识别并执行指令
    for (int line = 0; !halt; line++)
    {
        if (code[line][0] == '0')
        {
            if (code[line][1] == '0')
            {
                if (code[line][2] == '0')
                {
                    if (code[line][3] == '0')
                        BR(code[line]);
                    else
                        ADD(code[line]);
                }
                else
                {
                    if (code[line][3] == '0')
                    {
                        LD(code[line], code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)], line);
                    }
                    else
                        ST(code[line]);
                }
            }
            else
            {
                if (code[line][2] == '0')
                {
                    if (code[line][3] == '0')
                        JSR(code[line]);
                    else
                        AND(code[line]);
                }
                else
                {
                    if (code[line][3] == '0')
                        LDR(code[line]);
                    else
                        STR(code[line]);
                }
            }
        }
        else
        {
            if (code[line][1] == '0')
            {
                if (code[line][2] == '0')
                    NOT(code[line]);
                else
                {
                    if (code[line][3] == '0')
                        LDI(code[line]);
                    else
                        STI(code[line]);
                }
            }
            else
            {
                if (code[line][2] == '0')
                    JMP(code[line]);
                else
                {
                    if (code[line][0] == '0')
                        LEA(code[line]);
                    else
                        TRAP_HALT_ONLY();
                }
            }
        }
    }
    // 输出寄存器内容
    for (int i = 0; i < 8; i++)
    {
        printf("R%d = x%04hX\n", i, R[i]);
    }
    return 0;
}

unsigned short unsigned_binary_to_decimal(char c[], int start, int end)
{
    unsigned short a = 1;
    unsigned short ret = 0;
    int point = end;
    while (point >= start)
    {
        if(c[point] == '1')
            ret += a;
        a *= 2;
        point--;
    }
    return ret;
}

short signed_binary_to_decimal(char c[], int start, int end)
{
    short flag = 1;
    short ret = 0;
    // 复制字符串,防止更改原二进制码
    char code_copy[16];
    for (int i = 0; i < 16; i++)
    {
        code_copy[i] = c[i];
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

void BR(char c[])
{

}

void ADD(char c[])
{
    int DR = 0;
    int SR1 = 0;
    for (int i = 6; i >= 4; i--)
    {
        if (c[i] == '1')
            DR += pow(2, 6 - i);
    }
    for (int i = 9; i >= 7; i--)
    {
        if (c[i] == '1')
            SR1 += pow(2, 6 - i);
    }
    if(c[10] == '1')
        R[DR] = R[SR1] + signed_binary_to_decimal(c, 11, 15);
    else
    {
        int SR2 = 0;
        for (int i = 15; i >= 13; i--)
        {
            if (c[i] == '1')
                SR2 += pow(2, 6 - i);
        }
        R[DR] = R[SR1] + R[SR2];
    }
    //设置条件值
}
void LD(char c[],char b[],int line)
{
    int DR = 0;
    for (int i = 6; i >= 4; i--)
    {
        if(c[i] == '1')
            DR += pow(2, 6 - i);
    }
    R[DR] = unsigned_binary_to_decimal(b, 0, 15);
    //设置条件值
}

void ST(char c[])
{

}

void JSR(char c[])
{

}

void AND(char c[])
{

}

void LDR(char c[])
{

}

void STR(char c[])
{

}

void NOT(char c[])
{

}

void LDI(char c[])
{

}

void STI(char c[])
{

}

void JMP(char c[])
{

}

void LEA(char c[])
{

}

void TRAP_HALT_ONLY()
{
    halt = 1;
}