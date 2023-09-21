#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short unsigned_binary_to_decimal(char c[], int start, int end);
short signed_binary_to_decimal(char c[], int start, int end);
void BR(char c[], unsigned short *line);
void ADD(char c[]);
void LD(char c[], char b[], unsigned short line);
void JSR(char c[], unsigned short *line, unsigned short start_addres);
void AND(char c[]);
void NOT(char c[]);
void JMP(char c[], unsigned short *line, unsigned short start_address);
void LEA(char c[], unsigned short line, unsigned short start_address);
void TRAP_HALT_ONLY();
int set_condition_code_num(int DR);
int set_condition_code_string(char c[]);
int recon_Register(char c[], int start, int end);
void write_to_memory(char c[], unsigned short r);

unsigned short R[8] = {0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777, 0x7777};
int condition_code = 0;
int halt = 0;

int main()
{
    char code[60000][16] = {};
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
    }
    // 识别并执行指令
    int DR, SR, SR1, BaseR;
    unsigned short r,address;
    short offset6, offset9;
    for (unsigned short line = 0; !halt; line++)
    {
        unsigned short op_code = unsigned_binary_to_decimal(code[line], 0, 3);
        switch (op_code)
        {
        case 0:
            BR(code[line], &line);
            break;
        case 1:
            ADD(code[line]);
            break;
        case 2:
            LD(code[line], code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)], line);
            break;
        case 3://ST
            SR = recon_Register(code[line], 4, 6);
            r = R[SR];
            offset9 = signed_binary_to_decimal(code[line], 7, 15);
            write_to_memory(code[line + 1 + offset9], r);
            condition_code = set_condition_code_string(code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)]);
            break;
        case 4:
            JSR(code[line], &line, start_address);
            break;
        case 5:
            AND(code[line]);
            break;
        case 6://LDR
            DR = recon_Register(code[line], 4, 6);
            BaseR = recon_Register(code[line], 7, 9);
            offset6 = signed_binary_to_decimal(code[line], 10, 15);
            R[DR] = unsigned_binary_to_decimal(code[R[BaseR] + offset6 - start_address], 0, 15);
            condition_code = set_condition_code_num(DR);
            break;
        case 7://STR
            SR = recon_Register(code[line], 4, 6);
            BaseR = recon_Register(code[line], 7, 9);
            offset6 = signed_binary_to_decimal(code[line], 10, 15);
            address = offset6 + R[BaseR];
            r = R[SR];
            write_to_memory(code[address - start_address], r);
            condition_code = set_condition_code_string(code[address - start_address]);
            break;
        case 9:
            NOT(code[line]);
            break;
        case 10://LDI
            DR = recon_Register(code[line], 4, 6);
            offset9 = signed_binary_to_decimal(code[line], 7, 15);
            address = line + 1 + offset9;
            R[DR] = unsigned_binary_to_decimal(code[unsigned_binary_to_decimal(code[address], 0, 15) - start_address], 0, 15);
            condition_code = set_condition_code_num(DR);
            break;
        case 11://STI
            SR = recon_Register(code[line], 4, 6);
            offset9 = signed_binary_to_decimal(code[line], 7, 15);
            address = line + 1 + offset9;
            r = R[SR];
            write_to_memory(code[unsigned_binary_to_decimal(code[address], 0, 15) - start_address], r);
            condition_code = set_condition_code_string(code[unsigned_binary_to_decimal(code[address], 0, 15) - start_address]);
            break;
        case 12:
            JMP(code[line], &line, start_address);
            break;
        case 14:
            LEA(code[line], line, start_address);
            break;
        case 15:
            TRAP_HALT_ONLY();
            break;
        default:
            break;
        }
    }
    // 输出寄存器内容
    for (int i = 0; i < 8; i++)
        printf("R%d = x%04hX\n", i, R[i]);
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
    char code_copy[16] = "0000000000000000";
    for (int i = 0; i < 16; i++)
        code_copy[i] = c[i];
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
                    code_copy[point] = '0';
                    carry = 1;
                }
                else
                {
                    code_copy[point] = '1';
                    carry = 0;
                }
            }
            else
                break;//如果carry为0则后续carry均为0，直接结束即可
            point--;
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
    int DR = recon_Register(c,4,6);
    int SR1 = recon_Register(c,7,9);
    if(c[10] == '1')
        R[DR] = R[SR1] + signed_binary_to_decimal(c, 11, 15);
    else
    {
        int SR2 = 0;
        for (int i = 15; i >= 13; i--)
            if (c[i] == '1')
                SR2 += pow(2, 15 - i);
        R[DR] = R[SR1] + R[SR2];
    }
    condition_code = set_condition_code_num(DR);
}
void LD(char c[],char b[],unsigned short line)
{
    int DR = recon_Register(c, 4, 6);
    R[DR] = unsigned_binary_to_decimal(b, 0, 15);
    condition_code = set_condition_code_num(DR);
}
void JSR(char c[],unsigned short *line,unsigned short start_address)
{
    R[7] = *line + 1 + start_address;
    if (c[4] == '0')
    {
        int BaseR = recon_Register(c, 7, 9);
        *line = R[BaseR] - 1 - start_address;
    }
    else
    {
        short offset11 = signed_binary_to_decimal(c, 5, 15);
        *line = *line + offset11;
    }
        
}
void AND(char c[])
{
    int DR = recon_Register(c, 4, 6);
    int SR1 = recon_Register(c, 7, 9);
    if (c[10] == '1')
        R[DR] = R[SR1] & signed_binary_to_decimal(c, 11, 15);
    else
    {
        int SR2 = recon_Register(c, 13, 15);
        R[DR] = R[SR1] & R[SR2];
    }
    condition_code = set_condition_code_num(DR);
}
void NOT(char c[])
{
    int DR = recon_Register(c, 4, 6);
    int SR = recon_Register(c, 7, 9);
    R[DR] = ~R[SR];
    condition_code = set_condition_code_num(DR);
}
void JMP(char c[],unsigned short *line, unsigned short start_address)
{
    int BaseR = recon_Register(c, 7, 9);
    *line = R[BaseR] - start_address - 1;
}
void LEA(char c[], unsigned short line, unsigned short start_address)
{
    int DR = recon_Register(c, 4, 6);
    short offset9 = signed_binary_to_decimal(c,7,15);
    R[DR] = line + 1 + offset9 + start_address;
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
            if(c[i] == '1')
                return 1;
    return 0;
}
int recon_Register(char c[], int start, int end)
{
    int ret = 0;
    for (int i = end; i >= start; i--)
        if (c[i] == '1')
            ret += pow(2, end - i);
    return ret;
}
void write_to_memory(char c[],unsigned short r)
{
    for (int i = 15; i > -1; i--)
    {
        if (r % 2 == 1)
            c[i] = '1';
        else
            c[i] = '0';
        r = r / 2;
    }
}