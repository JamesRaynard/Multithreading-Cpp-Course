// Use std::atomic_flag to implement a spin lock
// which protects a critical section
#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

// The atomic_flag must be initialized as false
std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void task(int n)
{
	// test_and_set()
	// Returns true if another thread set the flag
	// Returns false if this thread set the flag
	while (lock_cout.test_and_set()) {}
	
	// Start of critical section
	// do some work
	using namespace std::literals;
	std::this_thread::sleep_for(50ms);
	std::cout << "I'm a task with argument " << n << '\n';
	// End of critical section
	
	// Clear the flag, so another thread can set it
	lock_cout.clear();
}

int main()
{
	std::vector<std::thread> threads;
	
	for (int i = 1; i <= 10; ++i)
	    threads.push_back(std::thread(task, i));
	
	for (auto& thr : threads)
		thr.join();
}