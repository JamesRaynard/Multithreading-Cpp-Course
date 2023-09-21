// Example of parallel vectorized execution policy
// Requires C++17 compiler
#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>

namespace se = std::execution;

int main() {
	std::vector<int> vec{ 3, 1, 4, 1, 5, 9 };
	
	// Sort the elements of vec in reverse order
	std::sort(se::par_unseq, vec.begin(), vec.end(),
                                     [](int a, int b) {
                                         return b < a;
	});

	for (auto i : vec)
		std::cout << i << ',';
	std::cout << '\n';
}