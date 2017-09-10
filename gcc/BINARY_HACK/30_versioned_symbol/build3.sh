gcc -fPIC -c -o libmax3.o libmax3.c
gcc -shared -Wl,-soname,libmax.so -Wl,--version-script,libmax3.def -o libmax.so.1.0 libmax3.o
#ln -s libmax.so.1.0 libmax.so

readelf -a libmax.so
