#include <iostream>
#include <functional>

int add(int x) { return x + 1; }

// https://leico.github.io/TechnicalNote/Cpp/lambda
void test_caputer()
{
	std::cout << "test_capture()" << std::endl;

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

void type_decl()
{
	std::cout << "type_decl()" << std::endl;
	int i = 0;
	int result = 0;
	std::function<int(int)> f = [](int x) { return x + 1;}; // OK

	auto f2 = [i](int x) { return i + 1;}; // OK
	std::function<int(int)> f3 = [i](int x) { return i + 1;}; // OK
	result = f3(2);

	std::cout << "result:"  << result  << std::endl;
	std::cout << "i:" << i << std::endl;

	{
	auto fi = [&](int x) { i = 10; return i + 1;}; // OK
	std::function<int(int)> fii = [&](int x) { i += 20; return i + 1;}; // OK
	result = fi(2);
	result = fii(2);
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
  type_decl();
}
