gcc -fPIC -shared -o stack_usage.so stack_usage.c

gcc -finstrument-functions main.c stack_usage.so -o a.out

LD_LIBRARY_PATH=. ./a.out
