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

using namespace std::literals;

// Very simple "Bank" class
class Bank {
public:
    void debit(const std::string& name, int amount)
	{
		std::cout << "Debiting " << amount << " from " << name << '\n';
	}
	
	void credit(const std::string& name, int amount)
	{
		std::cout << "Crediting " << amount << " to " << name << '\n';
	}
	void print(const std::string& name)
	{
		std::cout << "Displaying account for " << name << '\n';
	}
};

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
	// Transfer $1000 from Peter to Paul
	// Must be done as a single transaction	
	
	// Monitor wrapper for Bank class
	Monitor<Bank> mon;
	
	// Invoke its function call operator and
	// pass a callable object which takes a Bank argument
	mon([] (Bank bank) {
		// Call its member functions, all under the same lock
		bank.debit("Peter", 1000);
		bank.credit("Paul", 1000);
		bank.print("Peter");
		bank.print("Paul");
	});
	
	std::cout << "Done\n";
}