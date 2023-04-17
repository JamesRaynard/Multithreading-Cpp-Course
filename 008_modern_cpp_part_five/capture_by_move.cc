// Example of lambda expressions which capture by move
#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> strings(5);

	std::cout << "Capture by reference\n";

	// Lambda expression which captures "strings" by reference
	[&strings]() {
		std::cout << "Size in lambda = " << strings.size() << '\n';
	}();

	std::cout << "After calling lambda, size in main = " << strings.size() << '\n';

	std::cout << "\nCapture by move\n";
	
	// Lambda expression which captures "strings" by move
	// Create a new variable "vec_strings" which is local to the lambda body
	// Initialize it by moving "strings" into it
	[vec_strings = std::move(strings)] () {
		std::cout << "Size in lambda = " << vec_strings.size() << '\n';
	}();
	
	std::cout << "After calling lambda, size in main = " << strings.size() << "\n\n";
}