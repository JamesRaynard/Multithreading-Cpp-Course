// Example of std::partial_sum()
#include <numeric>
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec { 1, 2, 3, 4} ;
	std::vector<int> vec2(vec.size());
	
	// The elements of vec2 will be { 1, 1 + 2, 1 + 2 + 3, 1 + 2 + 3 + 4 };
	// vec2 will contain { 1, 3, 6, 10 };
	std::partial_sum(vec.begin(), vec.end(), vec2.begin());
	
	std::cout << "Vector elements: ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';
	
	std::cout << "Elements of partial sum vector: ";
	for (auto i : vec2)
		std::cout << i << ", ";
	std::cout << '\n';
}