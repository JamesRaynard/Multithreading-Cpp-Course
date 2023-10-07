// Example of std::transform_reduce()
// The * and + operators are overloaded
// Finds the greatest difference between the elements in two vectors
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

namespace se = std::execution;

int main()
{
	std::vector<double> expected{ 0.1, 0.2, 0.3, 0.4, 0.5 };
	std::vector<double> actual{ 0.09, 0.22, 0.27, 0.41, 0.52 };
	
	auto max_diff = std::transform_reduce(se::par, 
                                          begin(expected), end(expected),
                                          begin(actual),

                                          // Initial value for the largest difference
                                          0.0,

                                          //  "Reduce" operation
                                          [](auto diff1, auto diff2){ return std::max(diff1, diff2); },

                                          // "Transform" operation
                                          [](auto exp, auto act) { return std::abs(act-exp); }
	);

	std::cout << "Max difference is: " << max_diff << '\n';
}