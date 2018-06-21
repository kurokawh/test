#include <stdio.h>

void foo()
{
	printf("hello, before main\n");
}
void bar()
{
	printf("hello, after main\n");
}

namespace {
	struct foo_caller {
		foo_caller() {
			foo();
		}
		~foo_caller() {
			bar();
		}
	} caller;
}

int main()
{
	printf("hello, world\n");
	return 0;
}
