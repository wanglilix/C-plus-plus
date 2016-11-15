#include<stdio.h>

void FileFunc()
{
	printf("FileFunc\n");
}

void EditFunc()
{
	printf("EditFunc\n");
}

int max(int a,int b){return (a < b) ? b : a;}


void main()
{
	int (*fp)(int, int);
	typedef void (*funcp)();
	typedef int (*fp1)(int, int);
	fp1 pFp1 = max;
	funcp pfun= FileFunc;
	pfun();
	pfun = EditFunc;
	pfun();
	
	int a, b ,c, d;
	scanf("%d%d", &a, &b);
	fp = max;
	c = (*fp)(a,b);
	d = pFp1(a, b);
	printf("%d,%d,%d",a,b,c);
	printf("\n");
	printf("%d,%d,%d",a,b,d);
}