// Algorithm call with predicate
// Using lambda expression
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> vec{4, 2, 3, 5, 1};
	
	std::cout << "Elements of vector: ";
	
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// Call std::count_if() algorithm using a lambda expression as predicate
	auto n_even = std::count_if(vec.begin(), vec.end(), 
	
		// The lambda definition goes inside the call!
		[] (int n)
		{ 
			return (n % 2 == 0);
		}
	);

	std::cout << "The vector has " << n_even << " element(s) with even values\n";
}