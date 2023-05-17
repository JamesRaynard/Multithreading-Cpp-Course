// Mutex example
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::mutex mut;

// Shared variable
int x = 0;

void write()
{
	std::lock_guard<std::mutex> lck_guard(mut);

	// Start of critical section
	++x;
	// End of critical section
}

void read()
{
	std::lock_guard<std::mutex> lck_guard(mut);

	// Start of critical section
	using namespace std::literals;
	std::this_thread::sleep_for(100ms);
	// End of critical section
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	threads.push_back(std::thread(write));
	threads.push_back(std::thread(write));

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	for (auto& thr : threads)
		thr.join();
}