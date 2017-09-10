#include <stdio.h>

__attribute__((constructor))
void foo()
{
	printf("hello, before main\n");
}

__attribute__((destructor))
void bar()
{
	printf("hello, after main\n");
}

int main()
{
	printf("hello, world\n");
	return 0;
}
