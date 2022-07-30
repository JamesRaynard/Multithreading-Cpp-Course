#include <thread>
#include <iostream>

// Callable object - thread entry point
class greeter {
	public:
	void hello() {
		std::cout << "Hello, Member Function Thread!\n";
	}
};

int main() {
	greeter greet;
    std::thread t{ &greeter::hello, &greet };        // Create an instance of std::thread and initialize it with the task
    t.join();                                // Wait for the thread to complete
}
