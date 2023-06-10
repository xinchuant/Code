#include <stdio.h>
#include <stdlib.h>
typedef struct linklist /*这个结构类型包括三个域 */
{
    int number;        /*猴子的编号*/
    int mydata;        /* 猴子的定数 */
    struct linklist *next; /* 指向下一只猴子的指针 */
} linklist;
linklist *CreateCircle(int n);
linklist *DeleteNext(linklist *p); /* 删除单循环链表的p所指的下一个结点 */

/* 提示： 你所有的代码将由系统插入在此处 */
void printlist(linklist *head)
{
    linklist *p = head;
    printf("%d ", p->mydata);
    p = p->next;
    while (p!=head)
    {
        printf("%d ", p->mydata);
        p = p->next;
    }
    printf("\n");
}
int KingOfMonkey(int n, linklist *head);
int main()
{
    linklist *head;
    int i, n;
    scanf("%d", &n);
    head = CreateCircle(n); /*创建单向循环链表，返回最后一个结点的指针 */

    printf("The king is monkey[%d].\n", KingOfMonkey(n, head));
    return 0;
}
/* 请在这里填写答案 */
linklist *CreateCircle(int n)
{
    linklist *head = (linklist *)malloc(sizeof(linklist));
    scanf("%d", &head->mydata);
    head->number = 1;
    linklist *p = head;
    linklist *q = NULL;
    for (int i = 2; i <= n; i++)
    {
        q = (linklist *)malloc(sizeof(linklist));
        scanf("%d", &q->mydata);
        q->number = i;
        p->next = q;
        p = q;
    }
    p->next = head;
    return p;
}
linklist *DeleteNext(linklist *p)
{
    printf("Delete No:%d\n", p->next->number);
    linklist *q = p->next;
    p->next = q->next;
    free(q);
}
int KingOfMonkey(int n, linklist *head)
{
    linklist *p = head;
    int d;
    d = p->mydata;
    while(p->next!=p)
    {
        for (int i = 1; i < d;i++)
        {
            p = p->next;
        }
        d = p->next->mydata;
        DeleteNext(p);
    }
    return p->number;
}
