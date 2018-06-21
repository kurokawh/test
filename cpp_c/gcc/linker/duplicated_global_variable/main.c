#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void foo();
void bar();
void bar2();


extern int val;

int main(int argc, char** argv)
{
	printf("in main() val: %d\n", val);

	printf(__FILE__ " call foo()\n");
	foo();
	printf(__FILE__ " ret  foo()\n");
	printf(__FILE__ " call bar2()\n");
	bar2();
	printf(__FILE__ " ret  bar2()\n");
	return 0;
}

