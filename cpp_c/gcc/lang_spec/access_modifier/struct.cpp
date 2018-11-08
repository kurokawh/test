#include <stdio.h>

struct A;

struct B {
	int b;
	void test(A& arg);
};

struct A {
	int aa;
private:
	int a;
};

void B::test(A& arg)
{
	b = arg.aa; // OK: default modifier of struct is public
//	b = arg.a;  // NG: if set private explicitly.
}

int main(int argc, char** argv)
{
	A aa;
	B bb;
	bb.test(aa);
	return 0;
}

