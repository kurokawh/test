#include <setjmp.h>

jmp_buf buf;

banana() {
	printf("in banana()\n");
	longjmp(buf, 1);
	/* NOTREACHED */
	printf("you'll never see this, bacause I longjmp'd\n");
}

main()
{
	if (setjmp(buf)) {
		printf("back in main\n");
	} else {
		printf("first time through\n");
		banana();
	}
}
