#include<stdio.h>
#include<stdlib.h>

typedef struct _node
{
    int number;
    struct _node *next;
} node;

node *createcycle_list();
void printlist(node *head);

int main()
{
    node *head = createcycle_list();
    printlist(head);
}

node *createcycle_list()
{
    int n;
    scanf("%d", &n);
    node *head = (node *)malloc(sizeof(node));
    scanf("%d", &head->number);
    node *p = head;
    node *q = NULL;
    for (int i = 0; i < n-1;i++)
    {
        q = (node *)malloc(sizeof(node));
        scanf("%d", &q->number);
        p->next = q;
        p = q;
    }
    p->next = head;
    return head;
}
void printlist(node *head)
{
    node *p = head;
    printf("%d ", p->number);
    p = p->next;
    while(p!=head)
    {
        printf("%d ", p->number);
        p = p->next;
    }
    printf("\n");
}