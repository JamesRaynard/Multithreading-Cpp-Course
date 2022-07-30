#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "concurrent_queue_cv.h"
#include <atomic>
#include <thread>
#include <functional>

using Func = std::function<void()>;

class thread_pool {
	concurrent_queue_cv<Func> work_queue;
	std::vector<std::thread> threads;
	void worker();
public:
	thread_pool();
	~thread_pool();
	void submit(Func f);
};

#endif //THREAD_POOL_H