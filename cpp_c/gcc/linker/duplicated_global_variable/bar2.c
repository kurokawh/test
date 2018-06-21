#include <stdio.h>

int val = 2;
//extern int val;

void bar()
{
	printf(__FILE__ " in bar() val: %d\n", val);
	val++;
}

void bar2()
{
	printf(__FILE__ " in bar2() val: %d\n", val);
	val++;
}

//void foo()
void foo2()
{
	printf(__FILE__ " in foo() val: %d\n", val);
}
