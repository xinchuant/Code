#include <stdio.h>

void sort(int a[], int len);

int main(void)
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("y");
    sort(a, n);
    printf("y");
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }
}

void sort(int a[], int len)
{
    int b[1000000];
    for (int i = 0; i < len;i++)
    {
        b[a[i]]++;
    }
    int count = 0;
    for (int i = 0; i < 1000000;i++)
    {
        if(b[i]!=0)
        {
            for (;b[i]!=0;b[i]--)
            {
                a[count] = i;
                count++;
            }
        }
    }
}