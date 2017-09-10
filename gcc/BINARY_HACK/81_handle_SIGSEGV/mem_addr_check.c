#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

/*
 * check if given address is valid or not.
 * return siglongjmp(3) in order to avoid infinit loop which is caused 
 * if just return by SIGSEGV handler.
 */
static struct sigaction orig_act;
static sigjmp_buf env;

#define TRUE 1
#define FALSE 0

static void sigsegv_handler(int sig)
{
	siglongjmp(env, 1);
}

int validate(void* addr)
{
	int is_valid = FALSE;
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	act.sa_handler = sigsegv_handler;
	sigaction(SIGSEGV, &act, &orig_act);

	if (sigsetjmp(env, TRUE) == 0) {
		/*touch*/
		volatile char c;
		c = *((char*)addr); // read
		*((char*)addr) = c; // write
	  
		is_valid = TRUE;
	} else {
		is_valid = FALSE;
	}

	sigaction(SIGSEGV, &orig_act, NULL);

	return is_valid;
}

int main(int argc, char** argv)
{
	int a;
	printf("variable a: %s\n", (validate(&a) ? "valid" : "invalid"));
	printf("100       : %s\n", (validate((void*)100) ? "valid" : "invalid"));
	return 0;
}
