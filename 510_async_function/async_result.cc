// How to get a result from a task executed by std::async()
// Yet another bad Fibonacci implementation!
#include <iostream>
#include <future>
#include <chrono>

// Task which returns a value
unsigned long long fibonacci(unsigned long long n)
{
	if (n <= 1)
		return 1;
	return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
	std::cout << "Calling fibonacci(44)\n";
	
	// Call async() and store the returned future
	auto result = std::async(fibonacci, 44);
	
	using namespace std::literals;
	while (result.wait_for(1s) != std::future_status::ready) {
		std::cout << "Waiting for the result...\n";
		
		// Do some other work
		// ...
	}
	
	// Call get() when we are ready
	std::cout << result.get() << std::endl;
}
