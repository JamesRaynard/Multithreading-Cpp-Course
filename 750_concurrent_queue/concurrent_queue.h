// Simple concurrent queue implementation
// pop() throws an exception when the queue is empty
// push() throws an exception when the queue is full
#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>
#include <mutex>

// Exception types for when queue is empty or full
class concurrent_queue_empty : public std::runtime_error {
  public:
	concurrent_queue_empty() : std::runtime_error("Queue is empty") {}
	concurrent_queue_empty(const char *s) : std::runtime_error(s) {}
};

class concurrent_queue_full : public std::runtime_error {
  public:
	concurrent_queue_full() : std::runtime_error("Queue is full") {}
	explicit concurrent_queue_full(const char *s) : std::runtime_error(s) {}
};

// Concurrent queue class
template <class T>
class concurrent_queue {
	// Data members
	std::mutex mut;
	std::queue<T> que;
	int max{50};
  public:
    // Constructors
	concurrent_queue() = default;
	concurrent_queue(int max) : max(max) {};

	// Deleted special member functions
	concurrent_queue(const concurrent_queue&) = delete;
	concurrent_queue& operator =(const concurrent_queue&) = delete;
	concurrent_queue(concurrent_queue&&) = delete;
	concurrent_queue& operator =(concurrent_queue&&) = delete;
	
	// Member functions
	// Push an element onto the queue
	void push(T value) {
		std::lock_guard<std::mutex> lck_guard(mut);
		
		if (que.size() > max) {
			throw concurrent_queue_full();
		}
		
		que.push(value);
	}

	// Pop an element from the queue
	void pop(T& value) {
		std::unique_lock<std::mutex> uniq_lck(mut);
		
		if (que.empty()) {
			throw concurrent_queue_empty();
		}
		
		value = que.front();
		que.pop();
	}
};

#endif //CONCURRENT_QUEUE_H