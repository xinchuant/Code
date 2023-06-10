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
    for (int i = 0; i < n;i++)
    {
        List p = (List)malloc(sizeof(struct Node));
        scanf("%d", &p->Data);
        p->Next = NULL;
        head->Next = p;
        head = p;
    }
    return Head;
}       /* 细节在此不表 */
void Print(List L)
{
    List p = L->Next;
    while (p)
    {
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
} /* 细节在此不表 */

List Insert(List L, ElementType X)
{
    List p = (List)malloc(sizeof(struct Node));
    p->Data = X;
    List head = L;
    for (; head->Next && head->Next->Data<=X;head = head->Next)
        ;
    p->Next = head->Next;
    head->Next = p;
    return L;
}

int main()
{
    List L;
    ElementType X;
    L = Read();
    scanf("%d", &X);
    L = Insert(L, X);
    Print(L);
    return 0;
}

/* 你的代码将被嵌在这里 */
