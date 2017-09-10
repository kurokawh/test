gcc -fPIC -c -o libmax1.o libmax1.c
gcc -shared -Wl,-soname,libmax.so.1 -o libmax.so.1.0 libmax1.o
ln -s libmax.so.1.0 libmax.so.1
gcc -L. -lmax -o vertest1 vertest1.c
LD_LIBRARY_PATH=. ./vertest1
