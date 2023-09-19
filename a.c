#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short unsigned_binary_to_decimal(char c[], int start, int end);
short signed_binary_to_decimal(char c[], int start, int end);
void reconizing_instruction(char c[]);
void BR(char c[]);
void ADD(char c[]);
void LD(char c[]);
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
    char code[10000][16];
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
    //识别并执行指令
    // for (int line = 0; !halt;line++)
    // {
    //     reconizing_instruction(code[line]);
    // }
    //输出寄存器内容
    for (int i = 0; i < 8; i++)
    {
        printf("R%d = x%04hX\n", i, R[i]);
    }
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

void reconizing_instruction(char c[])
{
    if(c[0] == '0')
    {
        if(c[1] == '0')
        {
            if(c[2] == '0')
            {
                if(c[3] == '0')
                    BR(c);
                else
                    ADD(c);
            }
            else
            {
                if(c[3] == '0')
                    LD(c);
                else
                    ST(c);
            }
        }
        else
        {
            if(c[2] == '0')
            {
                if(c[3] == '0')
                    JSR(c);
                else
                    AND(c);
            }
            else
            {
                if(c[3] == '0')
                    LDR(c);
                else
                    STR(c);
            }
        }
    }
    else
    {
        if(c[1] == '0')
        {
            if(c[2] == '0')
                NOT(c);
            else
            {
                if(c[3] == '0')
                    LDI(c);
                else
                    STI(c);
            }
        }
        else
        {
            if(c[2] == '0')
                JMP(c);
            else
            {
                if(c[0] == '0')
                    LEA(c);
                else
                    TRAP_HALT_ONLY();
            }
        }
    }
}

void BR(char c[])
{

}

void ADD(char c[])
{

}
void LD(char c[])
{

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

}