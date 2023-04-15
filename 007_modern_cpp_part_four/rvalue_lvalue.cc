// Example of overloading on value type
#include <iostream>

// Define a moveable type
// (The compiler will provide move operators)
class Test {};

// Function which takes lvalue reference
void func(const Test& test)
{
	std::cout << "Lvalue reference\n";
}

// Function which takes rvalue reference
void func(Test&& test) {
	std::cout << "Rvalue reference\n";
}

int main()
{
	Test test;

	std::cout << "Argument is test variable:\t\t";
	func(test);

	std::cout << "Argument is temporary object:\t\t";
	func(Test());

	std::cout << "Argument through std::move():\t\t";
	func(std::move(test));
	std::cout << '\n';
}