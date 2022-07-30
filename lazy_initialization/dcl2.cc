#include <mutex>

class some_type {
	// ...
public:
	void do_it() { /*...*/ }
};

some_type *ptr{nullptr};         // Variable to be lazily initialized
std::mutex process_mutex;

void process() {
    std::unique_lock<std::mutex> lk(process_mutex);       // Protect ptr

    if (!ptr)
        ptr = new some_type;
    lk.unlock();
    ptr->do_it();
}

