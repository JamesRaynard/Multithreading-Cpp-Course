#include <mutex>

class some_type {
	// ...
public:
	void do_it() { /*...*/ }
};

std::mutex process_mutex;

void process() {
	static some_type *ptr{new some_type};            // Variable to be lazily initialized
    
     ptr->do_it();
}
