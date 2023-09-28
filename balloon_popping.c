#include<stdio.h>

int main()
{
    int n, height;
    scanf("%d %d", &n, &height);
    int ballon_positon[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &ballon_positon[i]);
    int positon_to_jump = ballon_positon[0];
    int ballon_popped = 1;
    
    return 0;
}