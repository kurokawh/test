#include <stdio.h>

int val = 1;
//extern int val;

void bar()
{
	printf(__FILE__" in bar() val: %d\n", val);
}

void foo()
{
	printf(__FILE__" in foo() val: %d\n", val);
}
