#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy

#include <unistd.h>
#include <sys/mman.h> // mprotect

double func()
{
	return 3.14;
}

void allow_execution(const void* addr)
{
	long pagesize = (int)sysconf(_SC_PAGESIZE);
//	long pagesize = PAGE_SIZE;
	char* p = (char*)((long)addr & ~(pagesize - 1L));
	mprotect(p, pagesize * 10L, PROT_READ|PROT_WRITE|PROT_EXEC);
}

int main(int argc, char** argv)
{
	void* p = malloc(1000);
	memcpy(p, func, 1000);
	allow_execution(p);
	printf("PI equals to %g\n", ((double (*)(void))p)()); // cause BUS ERROR
	return 0;
}
