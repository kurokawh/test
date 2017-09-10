gcc -fPIC -c -o libmax1.o libmax1.c
#gcc -shared -Wl,-soname,libmax.so.1 -o libmax.so.1.0 libmax1.o
#ln -s libmax.so.1.0 libmax.so.1
#gcc vertest1.c -L. -lmax -o vertest1
#>>> error
# /usr/bin/ld: cannot find -lmax
# collect2: ld returned 1 exit status

gcc -shared -Wl,-soname,libmax.so -o libmax.so.1.0 libmax1.o
ln -s libmax.so.1.0 libmax.so
gcc vertest1.c -L. -lmax -o vertest1 

# >> sample not to use -soname
#gcc -shared -o libmax.so libmax1.c
#gcc  vertest1.c -L. -lmax -o vertest1

LD_LIBRARY_PATH=. ./vertest1
