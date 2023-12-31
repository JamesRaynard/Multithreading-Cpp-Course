// A naive internally synchronized class
// Has a data member which is a mutex
// Each member function locks the mutex when called
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

// Very simple "Bank" class
class Bank {
	// Mutex to protect the data
	std::mutex mut;

	// Shared data
	// ...
public:
	void debit(const std::string& name, int amount)
	{
		std::lock_guard<std::mutex> lck(mut);
		std::cout << "Debiting " << amount << " from " << name << '\n';
	}

	void credit(const std::string& name, int amount)
	{
		std::lock_guard<std::mutex> lck(mut);
		std::cout << "Crediting " << amount << " to " << name << '\n';
	}
	void print(const std::string& name)
	{
		std::lock_guard<std::mutex> lck(mut);
		std::cout << "Displaying account for " << name << '\n';
	}
};

int main()
{
	// Transfer $1000 from Peter to Paul
	Bank bank;

	// Call its member functions
	// Each member function locks separately
	std::thread thr([&bank] {
		bank.debit("Peter", 1000);
		bank.credit("Paul", 1000);
		bank.print("Peter");
		bank.print("Paul");
		});

	thr.join();

	std::cout << "Done\n";
}