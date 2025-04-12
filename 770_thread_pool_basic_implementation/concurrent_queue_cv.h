// Simple concurrent queue implementation
// with condition variable
// pop() blocks when the queue is empty
// push() polls when the queue is full
#ifndef CONCURRENT_QUEUE_CV_H
#define CONCURRENT_QUEUE_CV_H

#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std::literals;

// Concurrent queue class
template <class T>
class concurrent_queue_cv {
	// Data members
	std::mutex mut;
	std::queue<T> que;
	std::condition_variable cond_var;
	int max{50};
public:
    // Constructors
	concurrent_queue_cv() = default;
	concurrent_queue_cv(int max) : max(max) {};
	
	// Deleted special member functions
	concurrent_queue_cv(const concurrent_queue_cv&) = delete;
	concurrent_queue_cv& operator =(const concurrent_queue_cv&) = delete;
	concurrent_queue_cv(concurrent_queue_cv&&) = delete;
	concurrent_queue_cv& operator =(concurrent_queue_cv&&) = delete;
	
	// Member functions
	// Push an element onto the queue
	void push(T value) {
		std::unique_lock<std::mutex> uniq_lck(mut);
		
		// If the queue is full, wait and try again
		while (que.size() > max) {
			uniq_lck.unlock();
			std::this_thread::sleep_for(50ms);
			uniq_lck.lock();
		}
		
		// Perform the push and notify
		que.push(value);
		cond_var.notify_one();
	}
	
	// Pop an element from the queue
	void pop(T& value) {
		std::unique_lock<std::mutex> uniq_lck(mut);
		
		// Block when the queue is empty
		cond_var.wait(uniq_lck, [this] {return !que.empty();});
		
		// Perform the pop
		value = que.front();
		que.pop();
	}
};

#endif //CONCURRENT_QUEUE_CV_H