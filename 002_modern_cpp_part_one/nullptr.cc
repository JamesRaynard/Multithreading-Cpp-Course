// Example of NULL versus C++11's nullptr
#include <iostream>

// Two functions which are overloaded
void func(int i)
{
	std::cout << "func(int) called\n";
}

void func(int *i)
{
	std::cout << "func(int *) called\n";
}

int main()
{
	func(NULL);
	func(nullptr);
}