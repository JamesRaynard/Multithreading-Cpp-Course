// Example of using a member function as a thread's entry point
#include <thread>
#include <iostream>

// Class whose member function
// will be used as the thread's entry point
class greeter {
public:
	void hello() {
		std::cout << "Hello, Member Function Thread!\n";
	}
};

int main() {
	// Create an object of the class
	greeter greet;

	// Create an std::thread object
	// Pass a pointer to the member function
	// and a pointer to the object to call it on
	std::thread thr(&greeter::hello, &greet);

	thr.join();
}
