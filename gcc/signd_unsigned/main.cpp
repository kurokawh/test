#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int32_t minus(uint64_t a, uint64_t b)
{
//	printf("lx: %016lx\n", a - b);
	return a - b;
}
int main(int argc, char** argv)
{
	uint32_t ui32_1 = 1;
//	uint32_t ui32_2 = 2;
	uint32_t ui32_3 = 3;;
//	uint64_t ui64_1, ui64_2, ui64_3;

	printf("x: %x\n", ui32_1 - ui32_3);
	printf("u: %u\n", ui32_1 - ui32_3);
	printf("d: %d\n", ui32_1 - ui32_3);

	printf("x: %x\n", minus(1, 3));
	printf("u: %u\n", minus(1, 3));
	printf("d: %d\n", minus(1, 3));


	printf("x: %x\n", minus(0xfffffffffffffffe, 0xffffffff00000000));
	printf("u: %u\n", minus(0xfffffffffffffffe, 0xffffffff00000000));
	printf("d: %d\n", minus(0xfffffffffffffffe, 0xffffffff00000000));
	return 0;
}
