#include <thread>
#include <future>
#include <iostream>

void promise_task_example() 
{
	auto meaning = std::packaged_task<int(int)>(
		[](int n) {return n;});

	auto result = meaning.get_future();
	auto t      = std::thread(std::move(meaning), 42);
		 
	std::cout << "the meaning of life: " << result.get() << "\n";
	t.join();
}

int main(int argc, char** argv)
{
	promise_task_example();
	return 0;
}
