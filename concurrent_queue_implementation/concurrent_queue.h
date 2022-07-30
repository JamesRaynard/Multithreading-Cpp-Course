#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>
#include <mutex>

class concurrent_queue_exception : public std::runtime_error {
	public:
	concurrent_queue_exception() : std::runtime_error("Queue is empty") {}
	concurrent_queue_exception(const char *s) : std::runtime_error(s) {}
};

template <class T>
class concurrent_queue {
	std::mutex m;
	std::queue<T> q;
public:
	concurrent_queue() = default;
	void push(T value) {
		std::lock_guard<std::mutex> lg(m);
		q.push(value);
	}

	void pop(T& value) {
		std::unique_lock<std::mutex> lg(m);
		if (q.empty()) {
			throw concurrent_queue_exception("Queue is empty");
		}
		value = q.front();
		q.pop();
	}
};

#endif //CONCURRENT_QUEUE_H