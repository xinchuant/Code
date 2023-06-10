#include<stdio.h>
#include<stdlib.h>
struct ListNode 
{
    int data;
    struct ListNode *next;
};
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
int main(void)
{
    struct ListNode *head = createlist();
    printlist(head);
}