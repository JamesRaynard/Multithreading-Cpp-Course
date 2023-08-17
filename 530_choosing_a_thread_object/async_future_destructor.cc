// async_future_destructor.cc
// The destructor for std::async() will block
// if launched with std::launch::async
#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std::literals;

void task()
{
	std::this_thread::sleep_for(5s);
	std::cout << "Task result: " << 42 << '\n';
}

void func()
{
	std::cout << "Calling async\n";
	auto result = std::async(std::launch::async, task);
}

int main()
{
	func();
	std::cout << "Task started\n";
}