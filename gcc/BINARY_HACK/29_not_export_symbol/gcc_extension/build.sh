g++ -o test.so -shared test.cc
nm --demangle -D test.so | grep func

echo "---"
g++ -o test.so --fvisibility=hidden -shared test.cc
nm --demangle -D test.so | grep func
