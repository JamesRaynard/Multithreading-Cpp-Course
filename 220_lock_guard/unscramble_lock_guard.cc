// Use std::lock_guard to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex print_mutex;

void task(std::string str)
{
	for (int i = 0; i < 5; ++i) {
		try {
			// Create an std::lock_guard object
			// This calls print_mutex.lock()
			std::lock_guard<std::mutex> lck_guard(print_mutex);

			// Start of critical section
			std::cout << str[0] << str[1] << str[2] << std::endl;

			// Critical section throws an exception
			throw std::exception();
			// End of critical section

			std::this_thread::sleep_for(50ms);
		}  // Calls ~std::lock_guard
		catch (std::exception& e) {
			std::cout << "Exception caught: " << e.what() << '\n';
		}
	}
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");

	thr1.join(); thr2.join(); thr3.join();
}