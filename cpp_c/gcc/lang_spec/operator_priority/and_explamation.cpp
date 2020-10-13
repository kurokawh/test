// https://msdn.microsoft.com/ja-jp/library/126fe14k.aspx
// https://ja.wikipedia.org/wiki/C%E3%81%A8C%2B%2B%E3%81%AE%E6%BC%94%E7%AE%97%E5%AD%90

#include <stdio.h>

int main(int argc, char** argv)
{
	int a = 0x01;
	int b = 0x10;

	printf("a: %x\n", a);
	printf("b: %x\n",  b);
	printf("!a & b: %x\n", !a & b);
	printf("a & !b: %x\n", a & !b);

	return 0;
}
