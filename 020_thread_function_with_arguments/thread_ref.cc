// Example of passing arguments to a thread function by reference
#include <thread>
#include <iostream>
#include <string>

// Thread entry point
void hello(std::string& s) {
	s = "xyz";
}

int main() {
	std::string str = "abc" ;
	
	// Wrap argument in a call to std::ref()
	std::thread thr(hello, std::ref(str));
	thr.join();
	
	// Verify that it has been modified
	std::cout << "str is now " << str << '\n';
}