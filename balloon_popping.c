#include<stdio.h>

int main()
{
    int n, height;
    scanf("%d %d", &n, &height);
    int ballon_positon[n];
    int positon_to_jump = ballon_positon[0];
    int ballon_popped = 1;
    int ballon_interval[n - 1];
    for (int i = 0; i < n; i++)
        scanf("%d", &ballon_positon[i]);
    for (int i = 1; i < n; i++)
    {
        ballon_interval[i - 1] = ballon_positon[i] - ballon_positon[i - 1];
    }
    return 0;
}