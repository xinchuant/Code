#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int data;
    struct ListNode *next;
};

struct ListNode *createlist(); /*裁判实现，细节不表*/
struct ListNode *mergelists(struct ListNode *list1, struct ListNode *list2);
void printlist(struct ListNode *head)
{
    struct ListNode *p = head;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    struct ListNode *list1, *list2;

    list1 = createlist();
    list2 = createlist();
    list1 = mergelists(list1, list2);
    printlist(list1);

    return 0;
}

/* 你的代码将被嵌在这里 */
struct ListNode *createlist()
{
struct ListNode *p, *Head = NULL;
int x;
scanf("%d", &x);
while (x != -1)
{
    p = (struct ListNode *)malloc(sizeof(struct ListNode));
    p->data = x;
    p->next = Head;
    Head = p;
    scanf("%d", &x);
}
return Head;
}
struct ListNode *mergelists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode *head = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *p = head, *p1 = list1, *p2 = list2;
    while(p1&&p2)
    {
        if(p1->data>p2->data)
        {
            p->next = p1;
            p1 = p1->next;
            p = p->next;
        }
        else
        {
            p->next = p2;
            p2 = p2->next;
            p = p->next;
        }
        p->next = p1 ? p1 : p2;
    }
    return head->next;
}