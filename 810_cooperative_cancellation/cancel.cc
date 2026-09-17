// Example of cancelling an std::thread
#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

// Thread to be cancelled
// Task function with token as first argument
void guess(std::stop_token token, int target)
{
	int input{0};
	
	std::cout << "You have 10 seconds to guess the secret number!\n";
	
	while (input != target) {
		std::cout << "Enter your guess: ";
		std::cin >> input;
		  
		// On each iteration, check for a cancellation request
		if (token.stop_requested()) {
			std::cout << "Sorry, you have taken too long!\n";
			return;
		}
	}
	
	std::cout << "Correct! The secret number is " << input << '\n';
}

int main()
{
	// Create a stop source object
	std::stop_source stop_src;
	
	// Start the thread and pass the object's token
	std::thread guessing{ guess, stop_src.get_token(), 42};

	using namespace std::chrono;
	std::this_thread::sleep_for(10s);
	
	// Send a cancellation request
	stop_src.request_stop();
	
	// Remember to join!
	guessing.join();
}
