#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

#define NUM 1000

void create_join()
{
//	std::thread t;
	std::vector<std::thread> tv;
	tv.reserve(1000);

	for (int i = 0; i < NUM; i++ ) {
		tv[i] = std::thread([]() {return;});
	}
	for (int i = 0; i < NUM; i++ ) {
		tv[i].join();
	}
}

void create_detach()
{
//	std::thread t;
	std::vector<std::thread> tv;
	tv.reserve(1000);

	for (int i = 0; i < NUM; i++ ) {
		tv[i] = std::thread([]() {return;});
	}
	for (int i = 0; i < NUM; i++ ) {
		tv[i].detach();
	}
}

int main(int argc, char** argv)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();
	create_join();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
	std::cout << "create_join() elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::system_clock::now();
	create_detach();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
	std::cout << "create_detach() elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
	return 0;
}
