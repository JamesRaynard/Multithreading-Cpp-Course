#include "thread_pool.h"

using namespace std;

void thread_pool::worker() {
	while (true) {
		Func task;
		work_queue.pop(task);
		task();
	}
}

thread_pool::thread_pool() {
	const unsigned thread_count = thread::hardware_concurrency();
	for (unsigned i = 0; i < thread_count; ++i)
		threads.push_back(thread{&thread_pool::worker, this});
}

thread_pool::~thread_pool() {
	for (auto& t: threads) {
		t.join();
	}
}

void thread_pool::submit(Func f) {
	work_queue.push(f);
}