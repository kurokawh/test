#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

class A {
	int a;
};

class B {
	int b;
	void test(A& arg) {
		b = arg.a
	}
};
int main(int argc, char** argv)
{
	A aa;
	B bb;
	bb.test(aa);
	printf("val: %d\n", -ex);
	return 0;
}

