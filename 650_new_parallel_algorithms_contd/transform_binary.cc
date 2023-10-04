// Example of std::transform() with two inputs
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec{1, 2, 3, 4};
	std::vector<int> vec2{5, 6, 7, 8};
	std::vector<int> vec3;
	
	// Add each element in v to the corresponding element in v2 and store the result in v3
	std::transform(std::transform(vec.begin(), vec.end(),
				   vec2.begin(),
		           std::back_inserter(vec3),
		           [](int n1, int n2) {return n1 + n2;}
	);

	// Display the first input vector
	std::cout << "First input vector:  ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// Display the second input vector
	std::cout << "Second input vector: ";
	for (auto i : vec2)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// Display the output vector
	std::cout << "Output vector: ";
	for (auto i : vec3)
		std::cout << i << ", ";
	std::cout << '\n';
}