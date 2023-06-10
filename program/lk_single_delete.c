#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int data;
    struct ListNode *next;
};

struct ListNode *readlist();
struct ListNode *deletem(struct ListNode *L, int m);
void printlist(struct ListNode *L)
{
    struct ListNode *p = L;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    int m;
    struct ListNode *L = readlist();
    scanf("%d", &m);
    L = deletem(L, m);
    printlist(L);

    return 0;
}

/* 你的代码将被嵌在这里 */
struct ListNode *readlist()
{
    struct ListNode *p,*Head = NULL;
    int x;
    scanf("%d", &x);
    while(x != -1)
    {
        p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->data = x;
        p->next = Head;
        Head = p;
        scanf("%d", &x);
    }
    return Head;
}
struct ListNode *deletem(struct ListNode *L, int m)
{
    for (struct ListNode *p = L, *q = NULL; p;)
    {
        if (p->data == m)
        {
            if(q)
            {
                q->next = p->next;
                free(p);
                p = q->next;
            }
            else
            {
                L = p->next;
                free(p);
                p = L;
            }
        }
        else
        {
            q = p;
            p = p->next;
        }
    }
    return L;
}