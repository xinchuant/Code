#include <stdio.h>
#include <math.h>
#include <string.h>

struct info
{
    double price;
    char name[100];
};

int main(void)
{
    int n;
    char c;
    scanf("%d", &n);
    struct info book[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%c", &c); // 此处读取缓冲区的\n是什么
        gets(book[i].name);
        scanf("%lf", &book[i].price);
    }
    int max = 0, min = 0;
    for (int i = 1; i < n; i++)
    {
        if (book[i].price < book[min].price)
        {
            min = i;
        }
        else if (book[i].price > book[max].price)
        {
            max = i;
        }
    }
    printf("%.2lf, %s\n%.2lf, %s", book[max].price, book[max].name, book[min].price, book[min].name);
    return 0;
}