// Thread pool with single queue
#include <iostream>
#include "thread_pool.h"

// Constructor
thread_pool::thread_pool() {
	thread_count = std::thread::hardware_concurrency() - 1;
	std::cout << "Creating a thread pool with " << thread_count << " threads\n";

	// Start the threads
	for (int i = 0; i < thread_count; ++i)
		threads.push_back(std::thread{&thread_pool::worker, this});
}

// Destructor
thread_pool::~thread_pool() {
	// Wait for the threads to finish
	for (auto& thr: threads) {
		thr.join();
	}
}

// Entry point function for the threads
void thread_pool::worker() {
	while (true) {
		Func task;
		
		// Take a task function off the queue
		work_queue.pop(task);
		
		// Invoke it
		task();
	}
}

// Add a task to the queue
void thread_pool::submit(Func func) {
	work_queue.push(func);
}
