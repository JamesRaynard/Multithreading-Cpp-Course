// std::shared_ptr and thread safety
// Operations which affect the pointed-to data are not safe
// They must be synchronized
#include <memory>
#include <thread>
#include <iostream>
#include <mutex>

// std::shared_ptr has an "atomic" reference counter
std::shared_ptr<int> shptr = std::make_shared<int>(42);

// Mutex to protect std::shared_ptr's data
std::mutex mut;

void func1()
{
	// Potentially conflicting access - must be protected
	std::lock_guard<std::mutex> lgd(mut);
	*shptr = 5;
}

void func2()
{
	// Potentially conflicting access - must be protected
	std::lock_guard<std::mutex> lgd(mut);
	*shptr = 7;
}

int main()
{
	std::cout << "shptr data: " << *shptr << '\n';

	std::thread thr1(func1);
	std::thread thr2(func2);

	thr1.join();
	thr2.join();

	std::cout << "shptr data: " << *shptr << '\n';
}