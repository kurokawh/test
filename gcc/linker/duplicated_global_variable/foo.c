#include <stdio.h>

void bar();

int val = 0;

// export foo() to Public
void foo()
{
	printf(__FILE__ " in foo() val: %d\n", val);
	bar();
}
