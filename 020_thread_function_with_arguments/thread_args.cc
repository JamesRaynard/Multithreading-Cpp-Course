// Example of passing an argument to a thread function
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello(std::string str) {
    std::cout << str << '\n';
}

int main() {
	// hello() takes a string argument
	std::thread thr(hello, "Hello, Thread!");
	
	thr.join();
}
