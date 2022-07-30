#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class concurrent_queue_cv {
	std::mutex m;
	std::queue<T> q;
	std::condition_variable cv;
public:
	concurrent_queue_cv() = default;
	void push(T value) {
		std::lock_guard<std::mutex> lg(m);
		q.push(value);
		cv.notify_one();
	}

	void pop(T& value) {
		std::unique_lock<std::mutex> lg(m);
		cv.wait(lg, [this] {return !q.empty();});
		value = q.front();
		q.pop();
	}
};