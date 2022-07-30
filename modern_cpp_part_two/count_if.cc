#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool is_even(int n) { 
	return (n % 2 == 0);
}

int main() {
	vector<int> v{4, 2, 3, 5, 1};
	
	cout << "Elements of vector: ";
	
	for (auto i : v)
		cout << i << ", ";
	cout << endl;
	
	// Call count_if algorithm using a function pointer as predicate
	auto n_even = count_if(v.begin(), v.end(), is_even);

/*	
	// Call count_if algorithm using a lambda expression as predicate
	auto n_even = count_if(v.begin(), v.end(), 
		// The lambda definition goes inside the call!
		[] (int n) { 
			return (n % 2 == 0);
		}
	);
*/
	cout << "The vector has " << n_even << " elements with even values" << endl;
}