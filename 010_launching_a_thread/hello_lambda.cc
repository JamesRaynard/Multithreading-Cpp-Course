// Example of using a lambda expression as a thread's entry point
#include <thread>
#include <iostream>

int main() {
	// Use a lambda expression as the thread's entry point
	std::thread thr([]() {
		std::cout << "Hello, Lambda Thread!\n";
	});

	thr.join();
}