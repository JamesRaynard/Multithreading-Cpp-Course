// Lazy initialization (multi-threaded)
// Uses the Double-checked Locking algorithm
#include <mutex>

class Test {
	// ...
public:
	void func() { /*...*/ }
};

Test *ptest = nullptr;            // Variable to be lazily initialized
std::mutex mut;

void process() {
    if (!ptest) {                     // First check of ptest
        std::lock_guard<std::mutex> lck_guard(mut);
        
        if (!ptest)                  // Second check of ptest
            ptest = new Test;   // Initialize ptest
    }
     ptest->func();
}

