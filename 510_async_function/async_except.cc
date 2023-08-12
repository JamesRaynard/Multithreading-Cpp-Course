// A task started by std::async() throws an exception
#include <future>
#include <iostream>
#include <thread>
#include <exception>
#include <chrono>

// Task which returns a value
int produce()
{
	int x = 42;
	
	using namespace std::literals;
	std::this_thread::sleep_for(2s);
	
	// Some code which may throw an exception
	if (1) {
		throw std::out_of_range("Oops");
	}
	
	std::cout << "Produce returning " << x << '\n';
	return x;
}

int main()
{
	// Call async() and store the returned future
	auto result = std::async(produce);

	// Get the result - may throw an exception
	std::cout << "Future calling get()...\n";
	try {
		int x = result.get();				           // Get the result
		std::cout << "Future returns from calling get()\n";
		std::cout << "The answer is " << x << '\n';
	}
	catch(std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}
