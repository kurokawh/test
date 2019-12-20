#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// check if vertual func can be overrided by non-vertual func.
// => non virtuan func can be called.

class A {
	int a;
public:
	virtual void test(A& arg) {
		printf("A::test(): %d\n", arg.a);
	}
	void publicFuncA() {
		printf("A::pulicFuncA(): \n");
	}
	void publicFuncB() {
		printf("A::pulicFuncB(): \n");
	}
protected:
	void protectedFuncA() {
		printf("A::pulicFuncA(): \n");
	}

};

class SubVirtual : public A {
	int b;
public:
	virtual void test(A& arg) {
		printf("SubVirtual::test()\n");
		A::test(arg);
		protectedFuncA();
	}
};

class SubNonVirtual : public A {
	int b;
public:
	void test(A& arg) {
		printf("SubNonVirtual::test()\n");
		A::test(arg);
		protectedFuncA();
	}
};

void test(A& a, const char* s)
{
	printf("== test(%s) ==>\n", s);
	a.test(a);
	a.publicFuncA();
	printf("<== test(%s) ==\n", s);
}
int main(int argc, char** argv)
{
	A* a = new A;
	A* spa = new SubVirtual;
	spa->test(*spa);
	spa->publicFuncA();

	test(*a, "A");
	test(*spa, "SubVirtual");
	A* snv = new SubNonVirtual;
	test(*snv, "SubNonVirtual");


	delete snv;
	delete a;
	delete spa;
	return 0;
}

