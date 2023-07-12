// Use std::mutex to protect a critical section
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

std::mutex mut;

void task(int n) {
	std::lock_guard<std::mutex> lg(mut);
	
	// Start of critical section
	// do some work
	using namespace std::literals;
	std::this_thread::sleep_for(50ms);
	std::cout << "I'm a task with argument " << n << '\n';
	// End of critical section
}

int main() {
	std::vector<std::thread> threads;
	
	for (int i = 1; i <= 10; ++i)
	    threads.push_back(std::thread(task, i));
	
	for (auto& thr : threads)
		thr.join();
}