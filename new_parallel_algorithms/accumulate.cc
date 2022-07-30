#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v {1, 2, 3, 4, 5, 6, 7, 8};
	auto sum = accumulate(v.begin(), v.end(), 0);           // Sum elements of v using initial value 0
	
	cout << "Vector elements: ";
	for (auto i : v)
		cout << i << ", ";
	cout << "\nSum of elements is " << sum << endl;
}