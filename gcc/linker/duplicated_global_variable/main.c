#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void bar();
void foo();


extern int val;

int main(int argc, char** argv)
{
	printf("in main() val: %d\n", val);

	printf("call foo()\n");
	foo();
	printf("ret  foo()\n");
	return 0;
}

