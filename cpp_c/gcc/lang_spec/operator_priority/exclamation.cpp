#include <stdio.h>

int main(int argc, char** argv)
{
	int a = 0;
	int b = 1;

	printf("a: %x\n", a);
	printf("b: %x\n",  b);
	printf("!a: %x\n", !a);
	printf("!b: %x\n", !b);
	printf("!!a: %x\n", !!a);
	printf("!!b: %x\n", !!b);

	return 0;
}
