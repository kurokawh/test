#include <thread>
#include <future>
#include <iostream>

void async_example() 
{
	auto meaning = [](int n) {return n;};
	auto result = std::async(std::move(meaning), 42);
	std::cout << "the meaning of life: " << result.get() << "\n";
}

int main(int argc, char** argv)
{
	async_example();
	return 0;
}
