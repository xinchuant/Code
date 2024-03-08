#include <stdio.h>
int main()
{
    int a[100];
    char mem[10];
    int val = 0;
    for (int i = 0; i < 10; i++)
        a[i] = 0;
    while(1)
    {
        scanf("%d", &val);
        if (!val)
            break;
        char temp;
        int k = 0;
        while (1)
        {
            scanf("%c", &temp);
            if(temp=='\n')
                break;
            mem[k] = temp;
            k++;
            //printf("%d\n", k);
        }
        //printf("%s", mem);
        val = val / k;
        for (int j = 0; j < k; j++)
            a[mem[j] - 97] += val;
    }
    int p = 0;
    for (int p = 0; p < 26; p++)
    {
        if(a[p])
            printf("%c : %.1f\n", p + 97, a[p]*0.004);
    }
        return 0;
}