#include <stdio.h>

class A;

class B {
private:
	int b;
public:
	void testOk(A* arg);
	void testNg(A* arg);
};

class A {
private:
	int a;
	friend void B::testOk(A*);
};

void B::testOk(A* arg)
{
	b = arg->a; // OK: this func can refer private member of A.
}
void B::testNg(A* arg)
{
//	b = arg->a; // NG: this func can NOT refer private member of A.
}

int main(int argc, char** argv)
{
	A aa;
	B bb;
	bb.testOk(&aa);
	bb.testNg(&aa);
	return 0;
}

