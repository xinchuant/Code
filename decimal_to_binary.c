#include <stdio.h>

int main()
{
    long int decimal;
    int binary[100];
    int count = 0;
    scanf("%ld", &decimal);
    while (decimal)
    {
        if(decimal%2==1)
        {
            binary[count] = 1;
        }
        else if(decimal%2==0)
        {
            binary[count] = 0;
        }
        count++;
        decimal = decimal / 2;
    }
    printf("%d digits in total\n", count+1);
    for (; count > -1; count--)
    {
        printf("%d", binary[count]);
    }
    printf("\n");
    return 0;
}