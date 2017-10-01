#include <atomic>
//#include <ctime>
#include <chrono>
#include <iostream>

#define multiplier 1

void atomic_example()
{
	typedef unsigned long long counter_t;
	std::atomic<counter_t> x;
	for (counter_t i = 0, iterations = 10'000'000 * multiplier; i < iterations; ++i) {
		x = i;
	}
}

void non_atomic_example()
{
	typedef unsigned long long counter_t;
	counter_t x;
	for (counter_t i = 0, iterations = 10'000'000 * multiplier; i < iterations; ++i) {
		x = i;
	}
}

int main(int argc, char** argv)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();
	atomic_example();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
	std::cout << "atomic_example() elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::system_clock::now();
	non_atomic_example();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
	std::cout << "atomic_example() elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
	return 0;
}
