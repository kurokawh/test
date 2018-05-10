gcc -c foo.c
ar rcs libfoo.a foo.o

gcc -c bar.c bar2.c
ar rcs libbar.a bar.o

gcc main.c -L. -lfoo -lbar

