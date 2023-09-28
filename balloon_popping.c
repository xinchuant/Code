#include<stdio.h>
int main()
{
    int n, height;
    scanf("%d %d", &n, &height);
    int ballon_positon[n];
    int counted_distance = 0;
    int positon_to_jump = ballon_positon[0] - height;
    int ballon_popped = 1;
    int ballon_popped_max = 1;
    int ballon_interval[n - 1];
    for (int i = 0; i < n; i++)
        scanf("%d", &ballon_positon[i]);
    int j = 0;
    for (int i = 1; i < n; i++)
    {
        ballon_interval[i - 1] = ballon_positon[i] - ballon_positon[i - 1];
        counted_distance += ballon_interval[i-1];
        ballon_popped++;
        for (; counted_distance > height; j++)
        {
            counted_distance -= ballon_interval[j];
            ballon_popped--;
        }
        if(ballon_popped > ballon_popped_max)
        {
            ballon_popped_max = ballon_popped;
            positon_to_jump = ballon_positon[i] - height;
        }
    }
    printf("%d %d\n", positon_to_jump, ballon_popped_max);
    return 0;
}