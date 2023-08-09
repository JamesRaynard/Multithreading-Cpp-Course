// Packaged task example
// Executes the task in the current thread
#include <future>
#include <iostream>
#include <chrono>

using namespace std::literals;

int main()
{
	// Packaged task object
	// The callable object is a lambda expression
	// It takes int and int arguments
	// It returns int
	std::packaged_task<int(int, int)> ptask([](int a, int b) {
		std::this_thread::sleep_for(2s);
		return a + b;
		});

	// The promise object is an std::promise<int>
	// Get the future associated with it
	std::future<int> fut = ptask.get_future();

	// Invoke the packaged task in this thread
	ptask(6, 7);

	std::cout << "Waiting for result\n";

	// Call get() to receive the result of the packaged task
	std::cout << "6 + 7 is " << fut.get() << '\n';
}