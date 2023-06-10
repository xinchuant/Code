#include "pstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word
{
   char letter;
   struct word *next;
} WORD;

void lk_free(WORD *head)
{
   WORD *now;
   for (now = head->next; now != NULL;)
   {
      free(head);
      head = now;
      now = now->next;
   }
   free(head);
}

PString *psCreate(const char* s)
{
   int L = strlen(s);
   PString *ps = (PString *)malloc(sizeof(int) * 1 + sizeof(char) * L);
   ps->length = L;
   for (int i = 0; i < L;i++)
   {
      ps->content[i] = s[i];
   }
   return ps;
}

void psFree(PString *ps)
{
   free(ps);
}

void psPrint(const PString *ps)
{
   for (int i = 0; i < ps->length;i++)
   {
      printf("%c", ps->content[i]);
   }
}

PString *psReadWord()
{
   WORD *now, *pt;
   WORD *head = (WORD *)malloc(sizeof(WORD));
   now = head;
   head->next = NULL;
   char temp;
   int count = 0;
   scanf("%c", &temp);
   for (; temp != '\n' && temp != ' '; count++)
   {
      pt = (WORD *)malloc(sizeof(WORD));
      pt->letter = temp;
      pt->next = NULL;
      now->next = pt;
      now = now->next;
      scanf("%c", &temp);
   }
   PString *ps = (PString *)malloc(sizeof(int) * 1 + sizeof(char) * count);
   ps->length = count;
   int i = 0;
   for (now = head->next; now != NULL; i++)
   {
      ps->content[i] = now->letter;
      now = now->next;
   }
   lk_free(head);
   return ps;
}

PString *psReadLine()
{
   WORD *now, *pt;
   WORD *head = (WORD *)malloc(sizeof(WORD));
   now = head;
   head->next = NULL;
   char temp;
   int count = 0;
   for (scanf("%c", &temp); temp != '\n'; scanf("%c", &temp))
   {
      pt = (WORD *)malloc(sizeof(WORD));
      pt->letter = temp;
      pt->next = NULL;
      now->next = pt;
      now = now->next;
      count++;
   }
   PString *ps = (PString *)malloc(sizeof(int) * 1 + sizeof(char) * count);
   ps->length = count;
   int i = 0;
   for (now = head->next; now != NULL; i++)
   {
      ps->content[i] = now->letter;
      now = now->next;
   }
   lk_free(head);
   return ps;
}

int psLength(const PString *ps)
{
   return ps->length;
}

PString *psClone(const PString *ps)
{
   PString *ps_copy = (PString *)malloc(sizeof(int)*1+sizeof(char)*ps->length);
   ps_copy->length = ps->length;
   for (int i = 0;i<ps->length;i++)
   {
      ps_copy->content[i] = ps->content[i];
   }
   return ps_copy;
}

PString *psConcat(const PString *ps1, const PString *ps2)
{
   int length = ps1->length + ps2->length;
   PString *ps3 = (PString *)malloc(sizeof(int)*1 + sizeof(char)*length);
   ps3->length = length;
   int i = 0;
   for (; i < ps1->length;i++)
   {
      ps3->content[i] = ps1->content[i];
   }
   for (;i<ps3->length;i++)
   {
      ps3->content[i] = ps2->content[i - ps1->length];
   }
   return ps3;
}

int psCompare(const PString *ps1, const PString *ps2)
{
   int sign = 0;
   int length_longer = 1;
   int min = ps2->length;
   if(ps1->length<ps2->length)
   {
      length_longer = 2;
      min = ps1->length;
   }
   else if(ps1->length == ps2->length)
   {
      length_longer = 0;
   }
   int i = 0;
   for (; i < min;i++)
   {
      if(ps1->content[i]==ps2->content[i])
      {
         continue;
         break;
      }
      else if(ps1->content[i] >ps2->content[i])
      {
         sign = 1;
      }
      else
      {
         sign = -1;
         break;
      }
   }
   if(!sign)
   {
      switch (length_longer)
      {
      case 0:
         break;
      case 1:
         sign = 1;
         break;
      case 2:
         sign = -1;
         break;
      }
   }
   return sign;
}

int psFindChar(const PString *ps, char ch)
{
   for (int i = 0; i < ps->length;i++)
   {
      if(ps->content[i] == ch)
      {
         return i;
      }
   }
   return -1;
}

int psFindString(const PString *ps1, const PString *ps2)//找到p1在p2中的位置
{
   if (ps1->length < ps2->length)
   {
      return -1;
   }
   int j;
   for (int i = 0; i <= (ps1->length - ps2->length); i++)
   {
      for (j = 0; j < ps2->length; j++)
      {
         if(ps2->content[j] != ps1->content[i+j])
         {
            break;
         }
      }
      if(j == ps2->length)
      {
         return i;
      }
   }
   return -1;
}

PString *psTrim(const PString *ps)
{
   int i, j;
   int sign = 0;
   for (i = 0; i < ps->length;i++)
   {
      if(ps->content[i]!=' ')
      {
         sign = 1;
         break;
      }
   }
   PString *ps1;
   if(!sign)
   {
      ps1 = (PString *)malloc(sizeof(int)*1);
      ps1->length = 0;
   }
   else
   {
      for (j = ps->length - 1; j > -1;j--)
      {
         if(ps->content[j]!=' ')
         {
            break;
         }
      }
      ps1 = (PString *)malloc(sizeof(int) * 1 + sizeof(char) * (j - i + 1));
      ps1->length = j - i + 1;
      for (int k = 0,l = i; k < j-i+1;k++,l++)
      {
         ps1->content[k] = ps->content[l];
      }
   }
   return ps1;
}

PString *psLower(const PString *ps)
{
   PString *ps1 = (PString *)malloc(sizeof(int) + sizeof(char) * ps->length);
   ps1->length = ps->length;
   for (int i = 0; i < ps->length;i++)
   {
      if(ps->content[i]<='Z'&&ps->content[i]>='A')
      {
         ps1->content[i] = ps->content[i] + 'a' - 'A';
      }
      else
      {
         ps1->content[i] = ps->content[i];
      }
   }
   return ps1;
}

PString *psUpper(const PString *ps)
{
   PString *ps1 = (PString *)malloc(sizeof(int) + sizeof(char) * ps->length);
   ps1->length = ps->length;
   for (int i = 0; i < ps->length; i++)
   {
      if (ps->content[i] <= 'z' && ps->content[i] >= 'a')
      {
         ps1->content[i] = ps->content[i] + 'A' - 'a';
      }
      else
      {
         ps1->content[i] = ps->content[i];
      }
   }
   return ps1;
}

PString *psSubstring(const PString *ps, int begin, int end)
{
   end--;
   PString *ps1 = (PString *)malloc(sizeof(int) + sizeof(char) * (end - begin + 1));
   ps1->length = end - begin + 1;
   for (int i = begin,j = 0; i < end + 1;i++,j++)
   {
      ps1->content[j] = ps->content[i];
   }
   return ps1;
}

PString *psReplace(const PString *ps, char ch1, char ch2)
{
   PString *ps1 = (PString *)malloc(sizeof(int) + sizeof(ps->length));
   ps1->length = ps->length;
   for (int i = 0; i < ps->length;i++)
   {
      if(ps->content[i] == ch1)
      {
         ps1->content[i] = ch2;
      }
      else
      {
         ps1->content[i] = ps->content[i];
      }
   }
   return ps1;
}

char psChar(const PString *ps, int index)
{
   return ps->content[index];
}

int psBeginWith(const PString *ps1, const PString *ps2)
{
   int sign = psFindString(ps1, ps2);
   if (sign == 0)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}