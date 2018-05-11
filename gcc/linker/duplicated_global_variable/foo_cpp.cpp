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
#ifdef REFER_A
	test();
#endif // REFER_A
}

class A {
public:
	A() {
		printf(__FILE__" in A() val: %d\n", val);
	}
};

A a;

#ifdef REFER_A
void test() {
	printf(__FILE__ " in test() a: %p\n", &a);
}
#endif // REFER_A
