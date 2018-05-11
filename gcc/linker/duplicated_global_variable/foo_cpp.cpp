#include <stdio.h>

extern "C" void bar2();
void test();

//int val = 0;
extern int val;

// export foo() to Public
extern "C" void foo()
{
	printf(__FILE__ " in foo() val: %d\n", val);
	bar2();
	test();
}

class A {
public:
	A() {
		printf(__FILE__" in A() val: %d\n", val);
	}
};

A a;

void test() {
	printf(__FILE__ " in test() a: %p\n", &a);
}
