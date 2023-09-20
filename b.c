#include<stdio.h>
#include<math.h>

int main()
{
    unsigned short a = 0;
    short b = -1;
    b = -b;
    unsigned short c = 0;
    c = a - b;
    printf("%d\n", c);
}