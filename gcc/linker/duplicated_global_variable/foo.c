#include <stdio.h>

void bar2();

//int val = 0;
extern int val;

// export foo() to Public
void foo()
{
	printf(__FILE__ " in foo() val: %d\n", val);
	bar2();
}
