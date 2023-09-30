// Example of std::reduce()
#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

namespace se = std::execution;

int main()
{
	std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};

	std::cout << "Vector elements: ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';

	// Sum the elements of vec, using initial value 0
	// Performed as four parallel additions
	// ((0 + 1) + (2 + 3) + (4 + 5) + (6 + 7))
	auto sum = std::reduce(se::par, vec.begin(), vec.end(), 0);

	std::cout << "The sum of the elements is " << sum << '\n';
}