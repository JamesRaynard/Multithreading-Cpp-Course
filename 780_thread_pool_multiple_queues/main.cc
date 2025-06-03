// Test program for thread pool with multiple queues
#include "thread_pool.h"
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std::literals;

// A task function
void task() {
	std::cout << "Thread id: " << std::this_thread::get_id() << " starting a task " << std::endl;
	std::this_thread::sleep_for(100ms);
	std::cout << "Thread id: " << std::this_thread::get_id() << " finishing a task " << std::endl;
}

int main() {
	// Create the thread pool
	thread_pool pool;
	
	// Send some tasks to the thread pool
	for (int i = 0; i < 20; ++i)
		pool.submit(task);
	
	pool.submit([&pool](){
		std::this_thread::sleep_for(1s);
		std::cout << "All tasks completed" << std::endl;
	});
}