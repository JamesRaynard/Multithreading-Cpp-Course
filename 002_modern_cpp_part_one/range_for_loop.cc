// Example of range-for loop
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec{4, 2, 3, 5, 1};
	
	std::cout << "Vector elements before: ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// We need to use a reference to modify the elements
	for (auto& i : vec)
		i += 2;
	
	std::cout << "Vector elements after: ";
	for (auto i : vec)
		std::cout << i << ", ";
}