#include <thread>
#include <iostream>

class thread_guard {
    std::thread t;
public:
    explicit thread_guard(std::thread t) : t(std::move(t)) {}   // explicit constructor prevents conversions

    ~thread_guard() {
        if (t.joinable()) t.join();                   // Join thread if not already joined
    }

    thread_guard(const thread_guard&) = delete;       // Deleted copy operators prevent copying
    thread_guard& operator=(const thread_guard&) = delete; 
	thread_guard(thread_guard&&) noexcept = default;       // Default move operators to allow moving
    thread_guard& operator=(thread_guard&&) noexcept = default;
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