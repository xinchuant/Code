#include <stdio.h>

int function_divisor(int a, int b);

int main()
{
    int a, b;
    scanf("%d,%d", &a, &b);
    printf("%d", function_divisor(a, b));
    return 0;
}

int function_divisor(int a, int b)
{
    int ret = 0;
    int x = a, y = b;
    if (a < b)
    {
        x = b;
        y = a;
    }
    int r = x % y;
    while (r != 0)
    {
        x = y;
        y = r;
        r = x % y;
    }
    ret = y;
    return ret;
}