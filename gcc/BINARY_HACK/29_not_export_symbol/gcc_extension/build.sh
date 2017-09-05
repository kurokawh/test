g++ -o test.so -shared test.cc
nm --demangle -D test.so | grep func
# all symbols are shown

echo "---"
g++ -o test.so -fvisibility=hidden -shared test.cc
nm --demangle -D test.so | grep func
# only EXPORT symbol is shown
