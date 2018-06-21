gcc -fPIC -c -o libmax2.o libmax2.c

gcc -shared -Wl,-soname,libmax.so -Wl,--version-script,libmax2.def -o libmax.so.1.0 libmax2.o
#ln -s libmax.so.1.0 libmax.so
gcc vertest2.c -L. -lmax -o vertest2

LD_LIBRARY_PATH=. ./vertest2

LD_LIBRARY_PATH=. ./vertest1
