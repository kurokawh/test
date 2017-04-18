#include <stdio.h>

void cpp(const char** cpp)
{
	printf("before cpp: %p, *cpp: %p, **cpp: %c\n", cpp, *cpp, **cpp);
	*cpp += 1;
//	**cpp = 'x'; // error: assignment of read-only location '* * cpp'
	cpp++;
	printf("after  cpp: %p, *cpp: %p, **cpp: %c\n", cpp, *cpp, **cpp);
}

void pp(char** pp)
{
	printf("before pp: %p, *pp: %p, **pp: %c\n", pp, *pp, **pp);
	*pp += 1;
	**pp = 'x';
	pp++;
	printf("after  pp: %p, *pp: %p, **pp: %c\n", pp, *pp, **pp);
}

void pcp(char* const* pcp)
{
	printf("before pcp: %p, *pcp: %p, **pcp: %c\n", pcp, *pcp, **pcp);
//	*pcp += 1;  // error: assignment of read-only location '* pcp'
	**pcp = 'x';
	pcp++;
	printf("after  pcp: %p, *pcp: %p, **pcp: %c\n", pcp, *pcp, **pcp);
}

void ppc(char** const ppc)
{
	printf("before ppc: %p, *ppc: %p, **ppc: %c\n", ppc, *ppc, **ppc);
	*ppc += 1;
	**ppc = 'x';
//	ppc++; //  error: increment of read-only parameter 'ppc
	printf("after  ppc: %p, *ppc: %p, **ppc: %c\n", ppc, *ppc, **ppc);
}


char ARRAY[4] = {'a', 'b', 'c', '\0'};
char* V = ARRAY;

const char* C1 = "c1c"; // C1 & C2 are same.
char const* C2 = "c2c";

//char* const C3 = "c3c"; // warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
char* const C3 = ARRAY;

int main(int argc, char** argv)
{
//	cpp(&V);  // error: invalid conversion from 'char**' to 'const char**' [-fpermissive]
	cpp(&C1);
	cpp(&C2);
//	cpp(&C3); // error: invalid conversion from 'char* const*' to 'const char**' [-fpermissive]


	pp(&V);
//	pp(&C1);  // error: invalid conversion from 'const char**' to 'char**' [-fpermissive]
//	pp(&C2);  // error: invalid conversion from 'const char**' to 'char**' [-fpermissive]
//	pp(&C3);  // error: invalid conversion from 'char* const*' to 'char**' [-fpermissive]

	pcp(&V);
//	pcp(&C1); // error: invalid conversion from 'const char**' to 'char* const*' [-fpermissive]
//	pcp(&C2); // error: invalid conversion from 'const char**' to 'char* const*' [-fpermissive]
	pcp(&C3);

	ppc(&V);
//	ppc(&C1);  // error: invalid conversion from 'const char**' to 'char**' [-fpermissive]
//	ppc(&C2);  // error: invalid conversion from 'const char**' to 'char**' [-fpermissive]
//	ppc(&C3);  // error: invalid conversion from 'char* const*' to 'char**' [-fpermissive]

	return 0;
}
