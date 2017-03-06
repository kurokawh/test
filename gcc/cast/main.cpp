// http://d.hatena.ne.jp/tt_clown/20091116/1258351378

#include <stdio.h>

#include <iostream>
#include <string>

class foo {
public:
    operator bool() const { return false; }
    operator int() const { return 100; }
    operator std::string() const { return std::string("Hello"); }
};

// 適当な関数
void put_int(int x) { std::cout << x << std::endl; }
void put_str(const std::string& x) { std::cout << x << std::endl; }



int main(int argc, char** argv)
{
    foo a;
    put_int(a); // 100 と出力される
    put_str(a); // "Hello" と表示される

	int i = a;
	std::string s = a;
	printf("i: %d, s: %s\n", i, s.c_str());
    return 0;
}
