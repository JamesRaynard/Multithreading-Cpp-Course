// Example of C++11 universal initialization
#include <iostream>
#include <string>
#include <vector>

int main()
{
	int x{7};                                         // Equivalent to int x = 7;
	std::string str{"Let us begin"};                  // Equivalent to string str("Let us begin");

	std::cout << "x = " << x << '\n';
	std::cout << "str = \"" << str << "\"\n";

	// Narrowing conversions are not allowed
	int y = 7.7;                                      // Legal, although compilers may warn
	//int y{7.7};                                     // Illegal
	std::cout << "y = " << y << '\n';

	// Can  be used with multiple initial values
	std::vector<int> vec{4, 2, 3, 5, 1};              // std::vector variable with elements 4, 2, 3, 5, 1

	std::cout << "vec = ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << ", ";
}