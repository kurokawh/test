#include <stdlib.h>
#include <stdio.h>

class Test
{
public:
	void normal() {
		static bool sbool = false;

		if (sbool) {
			printf("sbool is true\n");
		} else {
			printf("sbool is false (default).\n");
			sbool = true;
		}
	}
};

class Sub1 : public Test
{
public:
	Sub1() {
		printf("Sub1\n");
	}
};

class Sub2 : public Test
{
public:
	Sub2() {
		printf("Sub2\n");
	}
};

int main(int argc, char** argv)
{
	Sub1 s1;
	Sub2 s2;
	s1.normal();
	s2.normal();
	return 0;
}
