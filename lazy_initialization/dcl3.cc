#include <mutex>

class some_type {
	// ...
public:
	void do_it() { /*...*/ }
};

some_type *ptr{nullptr};            // Variable to be lazily initialized
std::mutex process_mutex;

void process() {
    if (!ptr) {                                                                                  // First check of ptr
        std::lock_guard<std::mutex> lk(process_mutex);
        
        if (!ptr)                  // Second check of ptr
            ptr = new some_type;   // Initialize ptr
    }
     ptr->do_it();
}

