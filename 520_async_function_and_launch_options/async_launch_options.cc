// async_launch_options.cc
// The different launch options for std::async()
#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std::literals;

int task()
{
	std::cout << "Executing task() in thread with ID: ";
	std::cout << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(5s);
	std::cout << "Returning from task()\n";
	return 42;
}

void func(const std::string& option = "default"s)
{
	std::future<int> result;

	if (option == "async"s)
		result = std::async(std::launch::async, task);
	else if (option == "deferred"s)
		result = std::async(std::launch::deferred, task);
	else
		result = std::async(task);

	std::cout << "Calling async with option \"" << option << "\"\n";
	std::this_thread::sleep_for(2s);
	std::cout << "Calling get()\n";
	std::cout << "Task result: " << result.get() << '\n';
}

int main()
{
	std::cout << "In main thread with ID: " << std::this_thread::get_id() << '\n';

	func("async");
	func("deferred");
	func("default");
}
