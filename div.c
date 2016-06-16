#include<stdio.h>

volatile int a;

int div(int b)
{
	return a/b;
}

int main()
{
	a=15;
	volatile int res=a/3;
	printf("result: %d\n", res );
	return 0;
}