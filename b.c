#include<stdio.h>
#include<math.h>
void change(char a[]);
int main()
{
    char a[10] = "apple";
    change(a);
    printf("%s", a);
}
void change(char a[])
{
    a[0] = 'c';
}