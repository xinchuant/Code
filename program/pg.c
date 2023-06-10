#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    int coef; /* 系数 */
    int exp;  /* 指数 */
    struct node *next;
} polynomial;
void print_polynomial(polynomial *head)
{
    int not_all_zero = 0;
    int whether_fist = 1;
    polynomial *p = head;
    if(!p)
    {
        printf("0");
    }
    else
    {
        while (p)
        {
            if(p->exp==0)
            {
                if(p->coef)
                {
                    not_all_zero = 1;
                }
                if(whether_fist)
                {
                    printf("%d", p->coef);
                    whether_fist = 0;
                }
                else
                {   
                    if(p->coef>0)
                    {
                        printf("+%d", p->coef);
                    }
                    else
                    {
                        printf("%d", p->coef);
                    }
                }
            }
            else 
            {
                if(p->coef==0)
                {
                    p = p->next;
                    continue;
                }
                else if (p->coef != 0)
                {
                    not_all_zero = 1;
                    if(whether_fist)
                    {
                        if(p->coef == 1)
                        {
                            printf("x^%d",p->exp);
                        }
                        else if(p->coef == -1)
                        {
                            printf("-x^%d", p->exp);
                        }
                        else
                        {
                        printf("%dx^%d", p->coef, p->exp);
                        }
                        whether_fist = 0;
                    }
                    else
                    {
                        if(p->coef == 1)
                        {
                            printf("+x^%d",p->exp);
                        }
                        else if(p->coef == -1)
                        {
                            printf("-x^%d", p->exp);
                        }
                        else 
                        {
                            (p->coef > 0) ? printf("+%dx^%d", p->coef, p->exp) : printf("%dx^%d", p->coef, p->exp);
                        }
                    }
                }
            }
            p = p->next;
        }
        if(!not_all_zero)
        {
            printf("0");
        }
    }
    printf("\n");
}

polynomial *copylist(polynomial *A)
{
    polynomial *a,*p,*q,*t;
    if(!A)
    {
        a = NULL;
    }
    else
    {
        a = (polynomial *)malloc(sizeof(struct node));
        q = A;
        a->coef = q->coef;
        a->exp = q->exp;
        a->next = NULL;
        p = a;
        q = q->next;
        for(;q;q = q->next)
        {
            t = (polynomial *)malloc(sizeof(struct node));
            t->coef = q->coef;
            t->exp = q->exp;
            t->next = NULL;
            p->next = t;
            p = p->next;
        }
    }
    return a;
}

polynomial *create_polynomial()//此处有误，不能将-x^0和x^0合并
{
    int n;
    scanf("%d", &n);
    polynomial *head = NULL;
    for (int i = 0; i < n;i++)
    {
        polynomial *p = (polynomial *)malloc(sizeof(polynomial));
        scanf(" %d %d", &p->coef,&p->exp);
        if(head == NULL)
        {
            p->next = head;
            head = p;
        }
        else
        {
            int done = 0;
            if (p->exp > head->exp)
            {
                p->next = head;
                head = p;
                done = 1;
            }
            polynomial *q = head;
            while((!done)&&q->next)
            {
                if(p->exp==q->exp)
                {
                    q->coef += p->coef;
                    free(p);
                    done = 1;
                    break;
                }
                else if(p->exp>q->next->exp)
                {
                    p->next = q->next;
                    q->next = p;
                    done = 1;
                    break;
                }
                else
                {
                    q = q->next;
                }
            }
            if(!done)
            {
                p->next = q->next;
                q->next = p;
            }
        }
    }
    return head;
}

polynomial *add_polynomial(polynomial *A, polynomial * B)//不能直接用A、B，会改变A、B。需要复制后操作。
{
    polynomial *a = copylist(A);
    polynomial *b = copylist(B);
    polynomial *temp,*p1 = a,*p2 = b;
    for (;p2;)
    {
        if(a == NULL)
        {
            a = b;
            break;
        }
        else
        {
            int done = 0;
            if (p2->exp > a->exp)
            {
                temp = p2->next;
                p2->next = p1;
                a = p2;
                p1 = a;
                p2 = temp;
                continue;
            }
            while((!done)&&p1->next)
            {
                if(p2->exp==p1->exp)
                {
                    done = 1;
                    p1->coef += p2->coef;
                    p1 = p1->next;
                    temp = p2;
                    p2 = p2->next;
                    free(temp);
                    break;
                }
                else if(p2->exp>p1->next->exp)
                {
                    done = 1;
                    temp = p2->next;
                    p2->next = p1->next;
                    p1->next = p2;
                    p1 = p1->next;
                    p2 = temp;
                    break;
                }
                else
                {
                    p1 = p1->next;
                }
            }
            if(!done)
            {
                if(p2->exp<p1->exp)
                {
                    temp = p2->next;
                    p2->next = p1->next;
                    p1->next = p2;
                    p2 = temp;
                }
                else if(p2->exp==p1->exp)
                {
                    p1->coef += p2->coef;
                    temp = p2;
                    p2 = p2->next;
                    free(temp);
                }
            }
        }
    }
    return a;
}

polynomial *subtract_polynomial(polynomial *A,polynomial *B)
{
    polynomial *a = copylist(A);
    polynomial *b = copylist(B);
    polynomial *temp,*p1 = a,*p2 = b;
    for (;p2;)
    {
        if(a == NULL)
        {
            a = b;
            for(;p2;p2 = p2->next)
            {
                p2->coef *= -1;
            }
            break;
        }
        else
        {
            int done = 0;
            if (p2->exp > a->exp)
            {
                p2->coef *= -1;
                temp = p2->next;
                p2->next = p1;
                a = p2;
                p1 = a;
                p2 = temp;
                continue;
            }
            while((!done)&&p1->next)
            {
                if(p2->exp==p1->exp)
                {
                    done = 1;
                    p1->coef = p1->coef - p2->coef;
                    p1 = p1->next;
                    temp = p2;
                    p2 = p2->next;
                    free(temp);
                    break;
                }
                else if(p2->exp>p1->next->exp)
                {
                    done = 1;
                    p2->coef *= -1;
                    temp = p2->next;
                    p2->next = p1->next;
                    p1->next = p2;
                    p1 = p1->next;
                    p2 = temp;
                    break;
                }
                else
                {
                    p1 = p1->next;
                }
            }
            if(!done)
            {
                if(p2->exp<p1->exp)
                {
                    p2->coef *= -1;
                    temp = p2->next;
                    p2->next = p1->next;
                    p1->next = p2;
                    p2 = temp;
                }
                else if(p2->exp==p1->exp)
                {
                    p1->coef = p1->coef - p2->coef;
                    temp = p2;
                    p2 = p2->next;
                    free(temp);
                }
            }
        }
    }
    return a;
}

polynomial *multiply_polynomial(polynomial *A,polynomial *B)
{
    polynomial *a = A;
    polynomial *b = B;
    polynomial *multi = NULL;
    for(;a;a = a->next)
    {
        for(;b;b = b->next)
        {
            polynomial *p = (polynomial *)malloc(sizeof(struct node));
            p->coef = a->coef*b->coef;
            p->exp = a->exp+b->exp;
            if(!multi)
            {
                p->next = multi;
                multi = p;
            }
            else
            {
                int done = 0;
                polynomial *q = multi;
                while((!done)&&q->next)
                {
                    if(p->exp==q->next->exp)
                    {
                        done = 1;
                        q->next->coef += p->coef;
                        free(p);
                        q = q->next;
                    }
                    else if(p->exp>q->next->exp)
                    {
                        p->next = q->next;
                        q->next = p;
                        done = 1;
                        break;
                    }
                    else
                    {
                        q = q->next;
                    }
                }
                if(!done)
                {
                    p->next = q->next;
                    q->next = p;
                }
            }
        }
        b = B;
    }
    return multi;
}

int main(void)
{
    polynomial *polyA, *polyB;
    
    polyA = create_polynomial(); /* 其中函数create_polynomial()用于读入并创建多项式A的链表，请自行实现 */
    polyB = create_polynomial(); /* 读入并创建多项式B的链表 */
    printf("A=");
    print_polynomial(polyA); /* 输出多项式A */
    printf("B=");
    print_polynomial(polyB); /* 输出多项式B */
    printf("A+B=");
    print_polynomial(add_polynomial(polyA, polyB));
    /* 输出多项式加A+B 的结果, 其中函数add_polynomial(polyA,polyB)将返回A+B的多项式，请自行实现*/
    printf("A-B=");
    print_polynomial(subtract_polynomial(polyA, polyB));
    /* 输出多项式减A-B 的结果，其中函数subtract_polynomial(polyA,polyB)返回A-B的多项式，请自行实现*/
    printf("A*B=");
    print_polynomial(multiply_polynomial(polyA, polyB));
    /* 输出多项式乘A*B 的结果，其中函数multiply_polynomial(polyA,polyB)返回A*B的多项式，请自行实现 */

    return 0;
}