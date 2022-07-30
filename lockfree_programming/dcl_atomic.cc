#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

class some_type {
	// ...
public:
	void do_it() { /*...*/ }
};

atomic<some_type *> ptr{nullptr};            // Variable to be lazily initialized
std::mutex process_mutex;

void process() {
    if (!ptr) {                                                                                  // First check of ptr
        std::lock_guard<std::mutex> lk(process_mutex);
        
        if (!ptr)                  // Second check of ptr
            ptr = new some_type;   // Initialize ptr
    }
     some_type *sp = ptr;
	 sp->do_it();
}

int main() {
	vector<thread> threads;
	
	for (int i = 0; i < 10; ++i)
		threads.push_back(thread{process});
	for (auto&t : threads)
		t.join();
}