// Example of std::transform_reduce()
#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

namespace se = std::execution;

int main()
{
	std::vector<int> x{1, 2, 3, 4, 5};
	std::vector<int> y{5, 4, 3, 2, 1};

	auto result = std::transform_reduce(se::par,              // Execution policy
										x.begin(), x.end(),   // Iterator range for first vector
                                        y.begin(),            // Start of second vector
                                        0);                   // Initial value of sum
	
	std::cout << "First vector:  ";
	for (auto i : x)
		std::cout << i << ", ";
	std::cout << '\n';
	
	std::cout << "Second vector: ";
	for (auto i : y)
		std::cout << i << ", ";
	std::cout << '\n';
	
	std::cout << "Result is " << result << '\n';            // Displays 35
}