// Example of std::inclusive_scan()
#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

namespace se = std::execution;

int main()
{
	std::vector<int> vec{ 1, 2, 3, 4 };
	std::vector<int> vec2(vec.size());

	// The elements of vec2 will be { 1, 1 + 2, 1 + 2 + 3, 1 + 2 + 3 + 4 };
	// vec2 will contain { 1, 3, 6, 10 };
	std::inclusive_scan(se::par, vec.begin(), vec.end(), vec2.begin());

	std::cout << "Vector elements: ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';

	std::cout << "Elements of inclusive scan vector: ";
	for (auto i : vec2)
		std::cout << i << ", ";
	std::cout << '\n';
}