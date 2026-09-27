// Example of cancellation with std::jthread
// The task is a free function

#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

// Task function with stop token as first argument
void guess(std::stop_token token, int target)
{
	int input{0};
	
	std::cout << "Guess the secret number!\n";
	
	while (input != target) {
		std::cout << "Enter your guess: ";
        std::cin >> input;
		
        // On each iteration, check for a cancellation request
		if (token.stop_requested()) {
			std::cout << "Sorry, you have taken too long!\n";
			return;
		}
	}
	std::cout << "Correct! The secret number was " << input << '\n';
}

int main()
{
	// Start the thread
	std::jthread guessing{guess, 42};
	
	using namespace std::chrono;
	std::this_thread::sleep_for(10s);
	
	// Send a cancellation request
	guessing.request_stop();
}
