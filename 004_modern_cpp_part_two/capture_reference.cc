#include <iostream>

int main()
{
	int n = 2;

	// Captures the local variable n by reference
	[&n] (int arg) { return (++n * arg); }(3);
	
	std::cout << "n = " << n << '\n';
}