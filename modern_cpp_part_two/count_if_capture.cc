#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	vector<int> v{4, 2, 3, 5, 1};
	
	cout << "Elements of vector: ";
	
	for (auto i : v)
		cout << i << ", ";
	cout << endl;
	
	int radix{3};
	// Call count_if algorithm using a lambda expression as predicate
	auto n_even = count_if(v.begin(), v.end(), 
		[radix] (int n) {                      // The lambda captures radix by value
			return (n % radix == 0);
		}
	);

	cout << "The vector has " << n_even << " elements which are exact multiples of " << radix << endl;
}