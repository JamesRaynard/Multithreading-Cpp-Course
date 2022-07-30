#include <mutex>

class some_type {
	// ...
public:
	void do_it() { /*...*/ }
};

some_type* ptr{nullptr};         // Variable to be lazily initialized

std::once_flag ptr_flag;         // The flag stores synchronization data

void process() {
	// Pass a callable object which performs the initialization
	std::call_once(ptr_flag, []() { ptr = new some_type; });
	ptr->do_it();
}
