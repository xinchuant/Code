#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int is_number(char *s,int end);
int find_operater(char *s,int* end);
int calculate(char *s,int end);

int main()
{
    //读取表达式
    char s[1000];
    int end = 0;
    char temp;
    scanf("%c", &temp);
    for (;temp != '\n';end++)
    {
        s[end] = temp;
        scanf("%c", &temp);
    }
    s[end] = 0;
    // printf("%s",s);
    // 处理空格

    //计算
    int result = calculate(s, end);
    printf("%d", result);
    return 0;
}
int is_number(char*s,int end)
{
    int ret = 1;
    for (int i = 0; i < end;i++)
    {
        if(s[i]>57||s[i]<48)
        {
            ret = 0;
            break;
        }
    }
    return ret;
}
int find_operater(char* s,int* end)//先判断有没有加减
{
    int flag = 0;//是否有加减的标志
    int location = -1;
    //printf("%d\n",*end);
    for (int i = *end - 1; i > -1;i--)
    {
        if (s[i] == '+' || s[i] == '-' )
        {
            location = i;
            flag = 1;
            break;
        }
        else if (s[i] == ')')
        {
            int count = 1;
            i--;
            for (; count != 0; i--)
            {
                if (s[i] == ')')
                {    
                    count++;
                }
                else if (s[i] == '(')
                {
                    count--;
                }
            }
            i++;
        }
    }
    if(!flag)
    {
        for (int i = *end - 1; i > -1; i--)
        {
            if (s[i] == '*' || s[i] == '/' || s[i] == '%')
            {
                location = i;
            }
            else if (s[i] == ')')
            {
                int count = 1;
                i--;
                for (; count != 0; i--)
                {
                    if (s[i] == ')')
                    {
                        count++;
                    }
                    else if (s[i] == '(')
                    {
                        count--;
                    }
                }
                i++;
            }
        }
    }
    return location;
}

int calculate_in_parentheses(char *s, int end)
{
    int ret = 0;
    return ret;
}

int calculate(char *s,int end)
{
    int result = 0;
    if(is_number)
    {
        result = atoi(s);
    }
    else
    {
        int location = find_operater(s, &end);
        if (location == -1)
        {
            int count = 0;
            for (int i = end - 1; i > -1; i--)
            {
                result = result + (s[i] - 48) * pow(10, count);
                count++;
            }
        }
        else
        {
            int left, right;
            char op = s[location];
            s[location] = '0';
            left = calculate(s, location);
            right = calculate(s + location + 1, end - location - 1);
            switch (op)
            {
            case '+':
                result = left + right;
                break;
            case '-':
                result = left - right;
                break;
            case '*':
                result = left * right;
                break;
            case '/':
                result = left / right;
                break;
            case '%':
                result = left % right;
                break;
            default:
                break;
            }
        }
    }
    return result;
}