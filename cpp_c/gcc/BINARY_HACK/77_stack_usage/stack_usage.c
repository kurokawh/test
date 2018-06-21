#include <stdio.h>
#include <stdlib.h>

#include <stddef.h> // ptrdiff_t

static ptrdiff_t max_usage = 0;

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void* func_address, void* call_site)
{
	extern void* __libc_stack_end;
	const ptrdiff_t usage = __libc_stack_end - __builtin_frame_address(0);
	if (usage > max_usage) max_usage = usage;
}
//void __cyg_profile_func_exit(void* func_address, void* call_site)

__attribute__((no_instrument_function, destructor))
static void print_usage()
{
	printf("stack usage: %td (byte)\n", max_usage);
}

