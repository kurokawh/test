#include <stdio.h>
#include <stdlib.h> // malloc

int main(int argc, char** argv)
{
	void* p = malloc(1000);
	free(p);
	free(p);
	return 0;
}
