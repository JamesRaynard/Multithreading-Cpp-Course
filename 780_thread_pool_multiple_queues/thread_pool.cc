// Thread pool with multiple queues
#include <iostream>
#include <mutex>
#include <chrono>

#include "thread_pool.h"

using namespace std::literals;

// Constructor
thread_pool::thread_pool() {
	thread_count = std::thread::hardware_concurrency() - 1;
	std::cout << "Creating a thread pool with " << thread_count << " threads\n";
	
	// Create a dynamic array of queues
	work_queues = std::make_unique<Queue []> (thread_count);

	// Start the threads
	for (int i = 0; i < thread_count; ++i) {
		threads.push_back(std::thread{&thread_pool::worker, this, i});
	}
}

// Destructor
thread_pool::~thread_pool() {
	// Wait for the threads to finish
	for (auto& thr: threads) {
		thr.join();
	}
}

// Entry point function for the threads
void thread_pool::worker(int idx) {
	while (true) {
		Func task;
		
		// Take a task function off the queue
		work_queues[idx].pop(task);
		
		// Invoke it
		task();
	}
}

// Add a task to the current thread's queue
void thread_pool::submit(Func func) {
	work_queues[pos].push(func);
	
	// Advance to the next thread's queue
	pos = (pos + 1) % thread_count;
}
