// Example of std::accumulate()
#include <numeric>
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec { 0, 1, 2, 3, 4, 5, 6, 7 };
	
	std::cout << "Vector elements: ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// Sum the elements of vec, using initial value 0
	// Performed in left-to-right order, one addition at a time
	// ((((0 + 1) + 2) + 3) + ...)
	auto sum = std::accumulate(vec.begin(), vec.end(), 0);
	
	std::cout << "The sum of the elements is " << sum << '\n';
}