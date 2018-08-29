#include <stdio.h>

struct Test {
    typedef int foo;
};

template <typename T> 
void f(typename T::foo) // 定義#1
{
	printf("void f(typename T::foo)\n");
}

template <typename T> 
void f(T)               // 定義#2
{
	printf("void f(T)\n");
}

// https://ja.wikipedia.org/wiki/SFINAE
int main(int argc, char** argv)
{
    f<Test>(10); // #1の呼び出し
    f<int>(10);  // #2の呼び出し（int::fooがないので#1では失敗するはずだが、SFINAEのおかげでコンパイルエラーにならず、#2が評価される）
	return 0;
}

