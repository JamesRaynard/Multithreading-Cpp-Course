// Example of a monitor class
// Has a data member which is a mutex
// Each member function locks the mutex when called
#include <future>
#include <string>
#include <iostream>
#include <mutex>
#include <vector>
#include <chrono>
#include <thread>

// Monitor class
// Can wrap any type
template <typename T>
class Monitor {
    // The object to be monitored
	T data;
	
	// Mutex to protect the object
    std::mutex mut;
public:
	// Default constructor
	Monitor<T>(T data = T{}) : data(data) {}
	
	// Function call operator
	// Argument is a callable object of type Func
	// which takes an argument of type T
    template <typename Func>
    auto operator() (Func func) {
		std::lock_guard<std::mutex> lck_guard(mut);
		
		// Call the function, protected by the lock
		return func(data);
	}	
};

int main()
{
	using namespace std::literals;
	
	// Monitor wrapper for std::string
	Monitor<std::string> str_mon("start: "s);
	
	// Vector to store returned futures from std::async()
	std::vector<std::future<void>> futs;
	
	for (int i = 0; i < 5; ++i) {
		futs.push_back(std::async([&str_mon, i] {
			// Invoke its function call operator and
	        // pass a callable object which takes an std::string argument
			str_mon([i](std::string& arg) {
				std::this_thread::sleep_for(10ms);
				arg += std::to_string(i) + ", " + std::to_string(i) + ", ";
			});
		
			// Invoke the function call operator again
			str_mon([](const std::string& arg) {
				std::cout << arg << '\n';
			});
		}));
	}
	
	for (auto& fut: futs)
		fut.wait();

	std::cout << "Done\n";
}