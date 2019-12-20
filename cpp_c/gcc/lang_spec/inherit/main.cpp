#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// check behavoir of "public" inheritance and "private" inheritance.
//

class A {
	int a;
public:
//	A() {printf("A::A()\n");}
//	virtual ~A() {printf("A::~A()\n");}
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

class SubPublicA : public A {
	int b;
public:
//	SubPublicA() {printf("SubPublicA::SubPublicA()\n");}
//	virtual ~SubPublicA() {printf("SubPublicA::~SubPublicA()\n");}
	virtual void test(A& arg) {
		printf("SubPublicA::test()\n");
		A::test(arg);
		protectedFuncA();
	}
};

class SubPrivateA : private A {
	int b;
public:
//	SubPrivateA() {printf("SubPrivateA::SubPrivateA()\n");}
//	virtual ~SubPrivateA() {printf("SubPrivateA::~SubPrivateA()\n");}
	virtual void test(A& arg) {
		printf("SubPrivateA::test()\n");
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
	SubPublicA* spa = new SubPublicA;
	spa->test(*spa);
	spa->publicFuncA();

	test(*a, "A");
	test(*spa, "SubPublicA");


	printf("== private test==>\n");
// compile error
//	a = new SubPrivateA; // 'A' is an inaccessible base of 'SubPrivateA'
	SubPrivateA* sp = new SubPrivateA;
//	sp->test(*sp); // 'A' is an inaccessible base of 'SubPrivateA'
	sp->test(*a);
	delete sp;

	delete a;
	delete spa;
	return 0;
}

