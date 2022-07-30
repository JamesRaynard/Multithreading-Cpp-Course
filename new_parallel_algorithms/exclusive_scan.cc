#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v {1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> v2;
	exclusive_scan(v.begin(), v.end(),  back_inserter(v2));
	
	cout << "Original vector elements: ";
	for (auto i : v)
		cout << i << ", ";
	
	cout << "\nExclusive scan vector elements: ";
	for (auto i : v2)
		cout << i << ", ";
}