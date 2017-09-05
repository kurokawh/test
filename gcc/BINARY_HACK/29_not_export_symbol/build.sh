gcc -fPIC -c a.c; gcc -fPIC -c b.c; gcc -shared -o libfoo.so a.o b.o
nm -D libfoo.so | grep -v '_'
# both of foo & bar are shown

gcc -fPIC -c a.c; gcc -fPIC -c b.c; gcc -shared -o libfoo.so a.o b.o -Wl,--version-script,libfoo.map
nm -D libfoo.so | grep -v '_'
# only foo is shown
