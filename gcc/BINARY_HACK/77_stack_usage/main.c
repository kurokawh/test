#include <stdio.h>

void test2()
{
	int i = 0;
	printf("test2()\n");
	return i;
}

void test1()
{
	int i = 0;
	printf("test1()\n");
	test2();
	return i;
}

int main(void)
{
	printf("main()\n");
	test1();
	test2();
	return 0;
}
