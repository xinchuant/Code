#include<stdio.h>
#include<math.h>

int main()
{
    unsigned short a = 0x0FFF;
    short b = -1;
    a = a + b;
    printf("x%04hX\n", a);
}