#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

using namespace std;
using namespace std::execution;

int main() {
	vector<int> v {1, 2, 3, 4, 5, 6, 7, 8};
	auto sum = reduce(v.begin(), v.end(), 0);           // Sum elements of v using initial value 0
	
	cout << "Vector elements: ";
	for (auto i : v)
		cout << i << ", ";
	cout << "\nSum of elements is " << sum << endl;
}