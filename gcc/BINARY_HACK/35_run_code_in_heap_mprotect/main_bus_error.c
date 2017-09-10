#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy

double func()
{
	return 3.14;
}

int main(int argc, char** argv)
{
	void* p = malloc(1000);
	memcpy(p, func, 1000);
	printf("PI equals to %g\n", ((double (*)(void))p)()); // cause BUS ERROR
	return 0;
}
