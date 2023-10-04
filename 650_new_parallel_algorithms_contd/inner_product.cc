// Example of std::inner_product()
#include <numeric>
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> x{1, 2, 3, 4, 5};
	std::vector<int> y{5, 4, 3, 2, 1};

	auto result = std::inner_product(x.begin(), x.end(),    // Iterator range for first vector
                                                y.begin(),  // Start of second vector
                                                0);         // Initial value of sum
	
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