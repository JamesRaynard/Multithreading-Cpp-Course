// Example of std::exclusive_scan()
#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

namespace se = std::execution;

int main()
{
	std::vector<int> vec{ 1, 2, 3, 4 };
	std::vector<int> vec2(vec.size());

	// The elements of vec2 will be { -1, 1 + (-1), 1 + 2 + (-1), 1 + 2 + 3 + (-1) }
	// vec2 will contain { -1, 0, 2, 5 };
	std::exclusive_scan(se::par_unseq, vec.begin(), vec.end(), vec2.begin(), -1);

	// This is equivalent to
	std::vector<int> vec3 { -1, 1, 2, 3 };
	std::vector<int> vec4(vec.size());
	std::inclusive_scan(vec3.begin(), vec3.end(), vec4.begin());

	std::cout << "Vector elements: ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';

	std::cout << "Elements of exclusive scan vector: ";
	for (auto i : vec2)
		std::cout << i << ", ";
	std::cout << '\n';

	std::cout << "Elements of inclusive scan vector: ";
	for (auto i : vec4)
		std::cout << i << ", ";
	std::cout << '\n';
}