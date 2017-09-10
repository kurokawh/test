gcc -Wall -Wextra -Wformat=2 -Wstrict-aliasing=2 double_free.c -o double_free

# not wark for mac?
MALLOC_CHECK_=0 ./double_free
MALLOC_CHECK_=1 ./double_free
MALLOC_CHECK_=2 ./double_free

