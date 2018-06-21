// https://msdn.microsoft.com/ja-jp/library/126fe14k.aspx
// https://ja.wikipedia.org/wiki/C%E3%81%A8C%2B%2B%E3%81%AE%E6%BC%94%E7%AE%97%E5%AD%90

#include <stdio.h>

int main(int argc, char** argv)
{
	// (==) operator is higher than (&) operator
	int x = 0x0010 & 0xFFFF == 0x0010;
	printf("0x0010 & 0xFFFF == 0x0010: %x\n", x);

	int x2 = (0x0010 & 0xFFFF) == 0x0010;
	printf("(0x0010 & 0xFFFF) == 0x0010: %x\n", x2);

	int x3 = 0x0010 & (0xFFFF == 0x0010);
	printf("0x0010 & (0xFFFF == 0x0010): %x\n", x3);

	return 0;
}



