// An algorithm's predicate function throws an exception
// The algorithm has an execution policy
#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>
#include <execution>

namespace se = std::execution;

int main()
{
	std::vector<int> vec{3,1,4,1,5,9};
	
	try {
		// Predicate throws an exception
		std::sort(se::seq, vec.begin(), vec.end(), [](int a, int b) {
			throw std::out_of_range("Oops"); return true;
		});
	}
	catch (std::exception& e) {
		std::cout << "Caught exception: " << e.what() << '\n';
	}
	
	for (auto v : vec)
		std::cout << v << ", ";
	std::cout << '\n';
}