#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int value;
    struct _node *next;
    struct _node *prev;
} Node;

typedef struct 
{
    Node *head;
    Node *tail;
} List;

void insert_head(List *list, int x)
{
    Node *n = (Node*)malloc(sizeof(Node));
    n->value = x;
    n->next = list->head;
    list->head = n;
}

void print(List *list)
{
    for (Node *p = list->head;p;p = p->next) 
    {
        printf("%d ", p->value);
    }
    printf("\n");
}

void clear(List *list)
{
    for (Node *p = list->head;p;) 
    {
        Node *q = p->next;
        free(p);
        p = q;
    }
    list->head = NULL;
}

int search(List *list, int x)
{
    int r = 0;
    Node *p;
    for ( p = list->head; p; p=p->next ) 
    {
        if ( p->value == x ) 
        {
            // r = 1;
            break;
        }
        r++;
    }
    return p?r:-1;
}

void append_tail(List *list, int x)
{
    Node *n = (Node*)malloc(sizeof(Node));
    n->value = x;
    n->next = NULL;
    Node *p;
    if ( list->head )
    {
        for ( p=list->head; p->next; p=p->next )
            ;
        p->next = n;
    } else {
        list->head = n;
    }
}

//  remove one and stop
//  remove one and go on to the next
//  remove one and the next
void shanchu(List *list, int x)
{
    for ( Node *p = list->head, *q = NULL; p;  ) 
    {
        if ( p->value == x ) 
        {
            if (q) 
            {
                q->next = p->next;
                free(p);
                p = q->next;
            } 
            else 
            {
                list->head = p->next;
                free(p);
                p = list->head;
            }
        } 
        else 
        {
            q=p, p=p->next;
        }
    }
}

void insert(List *list, int x)
{
    Node *n = (Node*)malloc(sizeof(Node));
    n->value = x;
    n->next = NULL;
    if ( x<list->head->value )
    for ( Node *p = list->head; p; p=p->next ) 
    {
        if ( p->next ) 
        {
            if ( x < p->next->value ) 
            {
                n->next = p->next;
                p->next = n;
                break;
            }
        } else 
        {

        }
    }
}

int main()
{
    List list = {NULL};
    while (1) 
    {
        int x;
        scanf("%d", &x);
        if ( x ==-1 ) break;
        insert_head(&list, x);
    }
    print(&list);
    int x;
    scanf("%d", &x);
    shanchu(&list, x);
    print(&list);
    clear(&list);
}