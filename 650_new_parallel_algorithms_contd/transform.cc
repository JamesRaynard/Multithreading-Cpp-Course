// Example of std::transform()
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec{1, 2, 3, 4};
	std::vector<int> vec2;
	
	// Double each element of vec and store the results in vec2
	std::transform(vec.begin(), vec.end(),
	               std::back_inserter(vec2),
        	       [] (int n) {return 2*n;}
	);

	// Display the input vector
	std::cout << "Input vector:  ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// Display the output vector
	std::cout << "Output vector: ";
	for (auto i : vec2)
		std::cout << i << ", ";
	std::cout << '\n';
}