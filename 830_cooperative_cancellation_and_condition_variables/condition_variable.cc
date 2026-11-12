// Example of cancelling an std::jthread which
// has called wait() on a condition variable

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <stop_token>

using namespace std::literals;

// Flag to signal an event
bool free_drinks{false};

// Mutex and condition variable
// to manage the flag
std::mutex mut;
std::condition_variable_any cond_var;

// Task function with stop token as argument
void alert(std::stop_token token)
{
	std::unique_lock<std::mutex> uniq_lck(mut);
	cond_var.wait(uniq_lck, token, [] { return free_drinks; });
	
	if (free_drinks) {
		std::cout << "Free drinks at the end of this lecture!\n";
	}
	else {
		std::cout << "Sorry...\n";
	}
}

int main()
{
	// Start the thread
	// Offer students free drinks
	std::jthread alerting{alert};
	
	using namespace std::literals;
	std::this_thread::sleep_for(1s);
	
	// I have changed my mind!
	// Send a cancellation request
	//alerting.request_stop();
	
	// Announce the event
	{
		std::lock_guard<std::mutex> lck_guard(mut);
		free_drinks = true;
		cond_var.notify_one();
	}
}
