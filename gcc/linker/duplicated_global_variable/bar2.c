#include <stdio.h>

extern int val;

void bar2()
{
	printf(__FILE__ " in bar2() val: %d\n", val);
}

void foo()
{
	printf(__FILE__ " in foo() val: %d\n", val);
}
