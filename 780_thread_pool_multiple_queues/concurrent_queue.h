// Simple concurrent queue implementation
// pop() busy waits when the queue is empty
#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>
#include <mutex>
#include <thread>

using namespace std::literals;

template <class T>
class concurrent_queue {
	std::mutex mut;
	std::queue<T> que;
	int max{50};
public:
	concurrent_queue() = default;
	concurrent_queue(int max) : max(max) {};
	
	void push(T value) {
		std::unique_lock<std::mutex> uniq_lck(mut);
		
		while (que. size() > max) {
			uniq_lck.unlock();
			std::this_thread::sleep_for(50ms);
			uniq_lck.lock();
		}
		
		que.push(value);
	}

	void pop(T& value) {
		std::unique_lock<std::mutex> uniq_lck(mut);
		
		while (que.empty()) {
			uniq_lck.unlock();
			std::this_thread::sleep_for(50ms);
			uniq_lck.lock();
		}
		
		value = que.front();
		que.pop();
	}
};

#endif //CONCURRENT_QUEUE_H