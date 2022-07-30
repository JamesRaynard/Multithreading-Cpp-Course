#include <thread>
#include <iostream>

// Functor class with overloaded () operator
class Hello {
	public:
	void operator()() { std::cout << "Hello, Thread!\n"; }
};

// Callable object - thread entry point
void hello() {
	std::cout << "Hello, Thread!\n";
}

int main() {
	// Create an instance of std::thread and initialize it with the task
	std::thread t{ hello };
	// std::thread t { [] () { std::cout << "Hello, Thread!\n";}};    // Lambda function
	// Hello hello;
	// std::thread t{ hello };
	// Wait for the thread to complete
	t.join();
}