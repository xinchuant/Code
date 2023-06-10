#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "pstring.h"
#define X content
#define L length 
//	create an object of PString with its content as s
PString* psCreate(const char* s){
	int len=strlen(s);
	PString *x=(PString*)malloc(sizeof(int)+len);
	x->L=len;
	for (int i=0;i<len;i++) x->X[i]=s[i];
	return x
}

//	release the object ps
void psFree(PString *ps){
	free(ps);
}

//	print ps
void psPrint(const PString* ps){
	for (int i=0;i<ps->L;i++){
		putchar(ps->X[i]);
	}
//	puts("");
}

//	read a word, which is seperated by space
char s[10101];
PString* psReadWord(){
	char ch;
	int len=0;
	while (1){
		ch=getchar();
		if (ch==' '||ch=='\n') break;
		s[len++]=ch;
	}
//	s[len++]=0;
	PString *x=(PString*)malloc(sizeof(int)+len);
	x->L=len;
	for (int i=0;i<len;i++) x->X[i]=s[i];
	return x;
}

//	read a line
PString* psReadLine(){
	char ch;
	int len=0;
	while (1){
		ch=getchar();
		if (ch=='\n') break;
		s[len++]=ch;
	}
//	s[len++]=0;
	PString *x=(PString*)malloc(sizeof(int)+len);
	x->L=len;
	for (int i=0;i<len;i++) x->X[i]=s[i];
	return x;
	
}

//	returns the number of characters in the PString object, i.e. the length of the string
int psLength(const PString* ps){
	return ps->L;
}

//	clone a PString object
//	return the new one
PString* psClone(const PString *ps){
	int len=ps->L;
	PString *x=(PString*)malloc(sizeof(int)+len);
	x->L=len;
	for (int i=0;i<len;i++) x->X[i]=ps->X[i];
	return x;
}

//	concat two PString into a new one
//	return the new one
PString* psConcat(const PString* ps1, const PString* ps2){
	int len1=ps1->L,len2=ps2->L;
	PString *x=(PString*)malloc(sizeof(int)+len1+len2);
	x->length=len1+len2;
	for (int i=0;i<len1;i++) x->X[i]=ps1->X[i];
	for (int i=len1;i<len1+len2;i++) x->X[i]=ps2->X[i-len1];
	return x;
}

//	compare two PString objects
//	returns -1 if ps1 is < ps2; 0 if ps1 == ps2; 1 if ps1 > ps2
int min(int a,int b){
	return (a>b?b:a);
}
int psCompare(const PString* ps1, const PString* ps2){
//	if (ps1->L<ps2->L) return 0;
	for (int i=0;i<min(ps1->length,ps2->length);i++){
		if (ps1->X[i]>ps2->X[i]) return 1;
		if (ps1->X[i]<ps2->X[i]) return -1;
	}
	if (ps1->length>ps2->length) return 1;
	if (ps1->length<ps2->length) return -1;
	return 0;
}

//	find the location of ch in the ps
//	return the location of the first ch in ps, -1 if ch is not in ps
int psFindChar(const PString* ps, char ch){
	for (int i=0;i<ps->length;i++){
		if (ps->X[i]==ch) return i;
	}
	return -1;
}

//	find the first location of ps2 in ps1
//	return the location, NULL is not found
int psFindString(const PString* ps1, const PString* ps2){
	for (int i=0;i<=ps1->length-ps2->length;i++){
		int flag=1;
		for (int j=i;j<=i+ps2->length-1;j++){
			if (ps1->X[j]!=ps2->X[j-i]){
				flag=0;break;
			}
		}
		if (flag) return i;
	}
	return -1;
}


//	turn every character in ps into lower case
//	return the new lowered string
PString* psLower(const PString* ps){
	int len=ps->L;
	PString *x=(PString*)malloc(sizeof(int)+len);
	x->L=len;
	for (int i=0;i<len;i++) x->X[i]=(ps->X[i]<='Z'&&ps->X[i]>='A'?ps->X[i]-'A'+'a':ps->X[i]);
	return x;
}

//	turn every character in ps into upper case
//	return the new uppered string
PString* psUpper(const PString* ps){
	int len=ps->L;
	PString *x=(PString*)malloc(sizeof(int)+len);
	x->L=len;
	for (int i=0;i<len;i++) x->X[i]=(ps->X[i]<='z'&&ps->X[i]>='a'?ps->X[i]-'a'+'A':ps->X[i]);
	return x;
}

//	take a subset of the string ps. The subset is from begin to end.
//	For example, psSubstring(psCreate(“0123456789”), 3,5) returns a PString as “345”
//	return the new extracted string
PString* psSubstring(const PString* ps, int begin, int end){
	end--;
	if (begin>end) return psCreate("");
	int len=ps->L;
	PString *x=(PString*)malloc(sizeof(int)+end-begin+1);
	x->L=end-begin+1;
	for (int i=begin;i<=end;i++) x->X[i-begin]=ps->X[i];
	return x;
}


//	get rid of the space at both end
//	return the new created string
PString* psTrim(const PString* ps){
	int i=0,j=ps->L-1;
	for (;ps->X[i]==' ';i++);
	for (;ps->X[j]==' ';j--);
	return psSubstring(ps,i,j+1);
}
//	replace every ch1 in ps with ch2
//	return the replaced string
PString* psReplace(const PString* ps, char ch1, char ch2){
	int len=ps->L;
	PString *x=(PString*)malloc(sizeof(int)+len);
	x->L=len;
	for (int i=0;i<len;i++) x->X[i]=(ps->X[i]==ch1?ch2:ps->X[i]);
	return x;
}

//	return the char at the index
char psChar(const PString* ps, int index){
	if (index>=ps->L) return -1;
	return ps->X[index];
}

//	return 1 if the ps1 begins with ps2, 0 otherwise
int psBeginWith(const PString* ps1, const PString* ps2){
	if (ps1->L<ps2->L) return 0;
	for (int i=0;i<ps2->length;i++){
		if (ps1->X[i]!=ps2->X[i]) return 0;
	}
	return 1;
}
