#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

class A {
	int a;
public:
	A() {printf("A::A()\n");}
	virtual ~A() {printf("A::~A()\n");}
	virtual void test(A& arg) {
		printf("A::test(): %d\n", arg.a);
	}
};

class B : public A {
	int b;
public:
	B () {printf("B::B()\n");}
	virtual ~B() {printf("B::~B()\n");}
	virtual void test(A& arg) {
		printf("B::test()\n");
		//printf("B::test(): %d\n", arg.a); // ERROR A::a is private
		//printf("B::test(): %d\n", this->a); // ERROR A::a is private
		A::test(arg);
	}
};
int main(int argc, char** argv)
{
//	A* a = new A;
	B* b = new B; // NOTE: default ctor of A is called at first, then B() is called.
//	a->test(*a);
	b->test(*b);
	delete b;     // NOTE: dtor of B is called at first, then ~A() is called automatically.
//	delete a;
	return 0;
}

