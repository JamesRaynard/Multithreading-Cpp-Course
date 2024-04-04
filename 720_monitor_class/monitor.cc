// Monitor class
// It wraps the protected object
// Each member function locks the mutex when called
// then forwards the call to the wrapped object
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

// Very simple "Bank" class
class Bank {
	// Shared data
	// ...
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

class BankMonitor {
	std::mutex mut;
	Bank bank;

public:
	void debit(const std::string& name, int amount) {
		// Lock the mutex and forward the call
		std::lock_guard<std::mutex> lck(mut);
		bank.debit(name, amount);
	}
	void credit(const std::string& name, int amount) {
		// Lock the mutex and forward the call
		std::lock_guard<std::mutex> lck(mut);
		bank.credit(name, amount);
	}
	void print(const std::string& name) {
		// Lock the mutex and forward the call
		std::lock_guard<std::mutex> lck(mut);
		bank.print(name);
	}
};

int main()
{
	// Transfer $1000 from Peter to Paul
	BankMonitor bank_mon;

	// Call its member functions
	// Each member function locks separately
	std::thread thr([&bank_mon] {
		bank_mon.debit("Peter", 1000);
		bank_mon.credit("Paul", 1000);
		bank_mon.print("Peter");
		bank_mon.print("Paul");
		});

	thr.join();

	std::cout << "Done\n";
}
