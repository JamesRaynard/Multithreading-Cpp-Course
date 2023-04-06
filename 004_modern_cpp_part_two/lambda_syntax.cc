// Examples of lambda expression syntex
#include <iostream>

int main()
{
	// In C++14, the compiler can deduce the return type
	[] (int arg) { return 2 * arg; };
	
	// In C++11, it must be specified with a trailing return type
	//[] (int arg) -> int { arg = 2 * arg; return arg; };
	
	// A lambda expression is a callable object
	// It can be invoked by putting () after the body, with any arguments
	[] (int arg) { return 2 * arg; }(3);
	
	// A lambda expression can be stored in a variable of type "auto"
	auto lam = [] (int arg) { return 2 * arg; };
	
	std::cout << "Calling lam with argument 3\n";
	std::cout << "Returns " << lam(3) << '\n';
}