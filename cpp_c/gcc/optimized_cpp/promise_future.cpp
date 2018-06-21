#include <thread>
#include <future>
#include <iostream>

void promise_future_example() 
{
	auto meaning = [](std::promise<int>& prom) {
		prom.set_value(42);
	};
		 
	std::promise<int> prom;
	std::thread(meaning, std::ref(prom)).detach();
		 
	std::future<int> result = prom.get_future();
	std::cout << "the meaning of life: " << result.get() << "\n";
}

int main(int argc, char** argv)
{
	promise_future_example();
	return 0;
}
