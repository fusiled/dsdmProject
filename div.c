#include<stdio.h>

volatile unsigned int a;

unsigned int div(unsigned int b)
{
	return a/b;
}

int main()
{
	a=15;
	volatile unsigned int res=a/3;
	printf("result: %d\n", res );
	return 0;
}