gcc -fPIC -shared -o weak.so weak.c
gcc weak-main.c ./weak.so -lm ; ./a.out
# 3.162278
gcc weak-main.c ./weak.so; ./a.out
# sqrt isn't available\n
