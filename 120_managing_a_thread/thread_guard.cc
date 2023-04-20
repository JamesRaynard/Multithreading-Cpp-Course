// Uses a wrapper class for std::thread
// Ensures safe destruction when an exception is throw
#include <thread>
#include <iostream>

class thread_guard {
	std::thread thr;
public:
	// Constructor takes rvalue reference argument (std::thread is move-only)
	explicit thread_guard(std::thread&& thr): thr(std::move(thr)) {
	}

	// Destructor - join the thread if necessary
	~thread_guard()
	{
		if (thr.joinable())
			thr.join();
	}

	thread_guard(const thread_guard&) = delete;       // Deleted copy operators prevent copying
	thread_guard& operator=(const thread_guard&) = delete;

	// The move assignment operator is not synthesized
};

// Callable object - thread entry point
void hello()
{
	std::cout << "Hello, Thread!\n";
}

int main()
{
	try {
		std::thread thr(hello);
		thread_guard tguard{std::move(thr)};

		//thread_guard tguard{std::thread(hello)};

		// Code which might throw an exception
		throw std::exception();

	} // Calls ~thread_guard followed by ~thread

	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}