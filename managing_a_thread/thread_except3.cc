#include <thread>
#include <iostream>

class thread_guard {
    std::thread t;
public:
    // Constructor takes rvalue reference argument (std::thread is move-only)
    explicit thread_guard(std::thread&& t) : t(std::move(t)) {}

    ~thread_guard() {
        if (t.joinable()) t.join();                   // Join thread if not already joined
    }

    thread_guard(const thread_guard&) = delete;       // Deleted copy operators prevent copying
    thread_guard& operator=(const thread_guard&) = delete; 
	thread_guard(thread_guard&&) noexcept = default;       // Default move constructor to allow moving
	
	// Move assignment operator
	// Clear up the old thread before overwriting it
    thread_guard& operator=(thread_guard&& arg) noexcept {
        if (t.joinable()) {
			t.join();
		}
        t = std::move(arg.t);
        return *this;
    }
};

// Callable object - thread entry point
void hello() {
	std::cout << "Hello, Thread!\n";
}

int main() {
	try {
		//std::thread t{ hello };
		thread_guard tg{ std::thread(hello) };
		throw std::exception();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught\n";
	}
}
