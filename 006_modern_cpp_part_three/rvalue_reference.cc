// Example of a function argument which is an rvalue reference
#include <iostream>

// The caller's object will be moved into x
void func(int&& x)
{
	std::cout << "Rvalue reference" << std::endl;
}

int main()
{
	func(2);

	int y = 2;
	//func(y);      // Error! Must be a moveable rvalue
}