#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short unsigned_binary_to_decimal(char c[], int start, int end);
short signed_binary_to_decimal(char c[], int start, int end);
void BR(char c[],unsigned short *line);
void ADD(char c[]);
void LD(char c[],char b[],unsigned short line);
void JSR(char c[],unsigned short *line,unsigned short start_addres);
void AND(char c[]);
void LDR(char c[]);
void STR(char c[]);
void NOT(char c[]);
void STI(char c[]);
void JMP(char c[]);
void LEA(char c[]);
void TRAP_HALT_ONLY();
int set_condition_code_num(int DR);
int set_condition_code_string(char c[]);

unsigned short R[8] = {0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777};
int condition_code = 0;
int halt = 0;

int main()
{
    char code[1000][16] = {};
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
        if (code[line][0] == '2') // 用于测试者结束输入指令
            break;
    }
    // 识别并执行指令
    for (unsigned short line = 0; !halt; line++)
    {
        if (code[line][0] == '0')
        {
            if (code[line][1] == '0')
            {
                if (code[line][2] == '0')
                {
                    if (code[line][3] == '0')
                        BR(code[line],&line);
                    else
                        ADD(code[line]);
                }
                else
                {
                    if (code[line][3] == '0')
                    {
                        LD(code[line], code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)], line);
                    }
                    else//ST
                    {
                        int SR = 0;
                        for (int i = 6; i >= 4; i--)
                        {
                            if (code[line][i] == '1')
                                SR += pow(2, 6 - i);
                        }
                        unsigned short r = R[SR];
                        for (int i = 15; i > -1; i--)
                        {
                            if (r % 2 == 1)
                                code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)][i] = '1';
                            else
                                code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)][i] = '0';
                            r /= 2;
                        }
                        condition_code = set_condition_code_string(code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)]);
                    }
                }
            }
            else
            {
                if (code[line][2] == '0')
                {
                    if (code[line][3] == '0')
                        JSR(code[line],&line,start_address);
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
                    if (code[line][3] == '0')//LDI
                    {
                        int DR = 0;
                        for (int i = 6; i >= 4; i--)
                        {
                            if (code[line][i] == '1')
                                DR += pow(2, 6 - i);
                        }
                        short offset9 = signed_binary_to_decimal(code[line], 7, 15);
                        unsigned short address = 0;
                        if(offset9 < 0)
                        {
                            offset9 = -offset9;
                            address = line + 1 - offset9;
                        }
                        else
                            address = line + 1 + offset9;
                        R[DR] = unsigned_binary_to_decimal(code[unsigned_binary_to_decimal(code[address], 0, 15)-start_address],0,15);
                        condition_code = set_condition_code_num(DR);
                    }
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

void BR(char c[],unsigned short *line)
{
    if ((c[4] == '1' && condition_code == -1) || (c[5] == '1' && condition_code == 0) || (c[6] == '1' && condition_code == 1))
        *line = *line + signed_binary_to_decimal(c, 7, 15);
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
            SR1 += pow(2, 9 - i);
    }
    if(c[10] == '1')
        R[DR] = R[SR1] + signed_binary_to_decimal(c, 11, 15);
    else
    {
        int SR2 = 0;
        for (int i = 15; i >= 13; i--)
        {
            if (c[i] == '1')
                SR2 += pow(2, 15 - i);
        }
        R[DR] = R[SR1] + R[SR2];
    }
    condition_code = set_condition_code_num(DR);
}
void LD(char c[],char b[],unsigned short line)
{
    int DR = 0;
    for (int i = 6; i >= 4; i--)
    {
        if(c[i] == '1')
            DR += pow(2, 6 - i);
    }
    R[DR] = unsigned_binary_to_decimal(b, 0, 15);
    condition_code = set_condition_code_num(DR);
}

void JSR(char c[],unsigned short *line,unsigned short start_address)
{
    R[7] = *line + 1 + start_address;
    if (c[4] == '0')
    {
        int BaseR = 0;
        for (int i = 9; i >= 7; i--)
        {
            if (c[i] == '1')
                BaseR += pow(2, 9 - i);
        }
        *line = R[BaseR] - 1;
    }
    else
    {
        short offset11 = signed_binary_to_decimal(c, 5, 15);
        if (offset11 < 0)
        {
            offset11 = -offset11;
            *line = *line - offset11;
        }
        else
            *line = *line + offset11;
    }
}

void AND(char c[])
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
            SR1 += pow(2, 9 - i);
    }
    if (c[10] == '1')
        R[DR] = R[SR1] & signed_binary_to_decimal(c, 11, 15);
    else
    {
        int SR2 = 0;
        for (int i = 15; i >= 13; i--)
        {
            if (c[i] == '1')
                SR2 += pow(2, 15 - i);
        }
        R[DR] = R[SR1] & R[SR2];
    }
    condition_code = set_condition_code_num(DR);
}

void LDR(char c[])
{

}

void STR(char c[])
{

}

void NOT(char c[])
{
    int DR = 0;
    int SR = 0;
    for (int i = 6; i >= 4; i--)
    {
        if (c[i] == '1')
            DR += pow(2, 6 - i);
    }
    for (int i = 9; i >= 7; i--)
    {
        if (c[i] == '1')
            SR += pow(2, 9 - i);
    }
    R[DR] = ~R[SR];
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

int set_condition_code_num(int DR)
{
    if(R[DR] == 0)
        return 0;
    else
    {
        unsigned short a = pow(2, 15);
        unsigned short flag = a & R[DR];
        if(flag == 0x8000)
            return -1;
        else
            return 1;
    }
}

int set_condition_code_string(char c[])
{
    if(c[0] == '1')
        return -1;
    else
        for (int i = 0; i < 16; i++)
        {
            if(c[i] == '1')
                return 1;
        }
    return 0;
}