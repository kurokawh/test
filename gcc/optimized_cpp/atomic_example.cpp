#include <atomic>

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
	atomic_example();
	non_atomic_example();
	return 0;
}
