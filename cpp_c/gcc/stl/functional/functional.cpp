#include <iostream>
#include <functional>

int add(int x) { return x + 1; }

// https://leico.github.io/TechnicalNote/Cpp/lambda
void test_caputer()
{
	int i = 5;
	int result = 0;

	{
		// not writable
		auto f = [i](int x) { /*i = 3;*/ return x + i + 1; };
		result = f(1);
		std::cout << "result:"  << result  << std::endl;
		std::cout << "i:" << i << std::endl;
	}
	{
		// not writable as well
		auto f = [=](int x) { /*i = 3;*/ return x + i + 1; };
		result = f(1);
		std::cout << "result:"  << result  << std::endl;
		std::cout << "i:" << i << std::endl;
	}

	{
		// ref: writable
		auto f = [&](int x) { i = 3; return x + i + 1; };
		result = f(1);
		std::cout << "result:"  << result  << std::endl;
		std::cout << "i:" << i << std::endl;
	}

}

int main()
{
  // 関数を代入
  std::function<int(int)> f = add;

  // 関数オブジェクトを代入
  f = [](int x) { return x + 1; };

  // 保持している関数を呼び出す
  int result = f(1);
  std::cout << result << std::endl;

  test_caputer();
}
