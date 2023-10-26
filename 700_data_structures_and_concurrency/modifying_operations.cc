// Conflicting operations on STL containers are not safe
// They must be synchronized
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>

// Shared vector
std::vector<int> vec;

// Mutex to protect std::vector's data
std::mutex mut;

void func1()
{
	// Potentially conflicting access - must be protected
	//std::lock_guard<std::mutex> lgd(mut);
	for (int i = 0; i < 100000; ++i)
		vec.push_back(i);
}

void func2()
{
	// Potentially conflicting access - must be protected
	//std::lock_guard<std::mutex> lgd(mut);
	for (int i = 100000; i < 200000; ++i)
		vec.push_back(i);
}

int main()
{
	std::thread thr1(func1);
	std::thread thr2(func2);

	thr1.join();
	thr2.join();

	std::cout << "shptr data: ";
	for (int i = 0; i < 200000; ++i)
		std::cout << vec[i] << ", ";

	std::cout << "Finished\n";
}