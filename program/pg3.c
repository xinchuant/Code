#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read()
{
    List Head = (List)malloc(sizeof(struct Node));
    List head = Head;
    Head->Next = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        List p = (List)malloc(sizeof(struct Node));
        scanf("%d", &p->Data);
        p->Next = NULL;
        head->Next = p;
        head = p;
    }
    return Head;
} /* 细节在此不表 */
void Print(List L)
{
    if(!L->Next)
    {
        printf("NULL");
    }
    else
    {
    List p = L->Next;
    while (p)
    {
        printf("%d ", p->Data);
        p = p->Next;
    }
    }
    printf("\n");
} /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List list1, List list2)
{
    List head = (List)malloc(sizeof(struct Node));
    head->Next = NULL;
    List q = NULL, p1 = list1->Next, p2 = list2->Next,p = head;
    while (p1&&p2)
    {
        if(p1->Data<=p2->Data)
        {
        p->Next = p1;
        p1 = p1->Next;
        p = p->Next;
        }
        else
        {
        p->Next = p2;
        p2 = p2->Next;
        p = p->Next;
        }
    }
    p->Next = (p1 ? p1 : p2);
    list1->Next = NULL;
    list2->Next = NULL;
    return head;
}