// Example of cancellation with std::jthread
// The task is a lambda expression

#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

int main()
{
	// Task function with stop token as argument
	auto guess = std::jthread([] (std::stop_token token)
	{
		int input{0};
		
		std::cout << "Guess the secret number!" << std::endl;
		
		while (input != 42) {
			std::cout << "Enter your guess: ";
            std::cin >> input;
			
			// On each iteration, check for a cancellation request
			if (token.stop_requested()) {
				std::cout << "Sorry, you have taken too long!" << std::endl;
				return;
			}
		}
		std::cout << "Correct! The secret number was " << input << std::endl;
	});

	using namespace std::chrono;
	std::this_thread::sleep_for(10s);
	
	// Send a cancellation request
	guess.request_stop();
}
