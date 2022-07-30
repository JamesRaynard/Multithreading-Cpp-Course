#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v {1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> v2;
	partial_sum(v.begin(), v.end(),  back_inserter(v2));              // v2 will contain { 1, 3, 6, 10 };
	
	cout << "Original vector elements: ";
	for (auto i : v)
		cout << i << ", ";
	
	cout << "\nPartial sum vector elements: ";
	for (auto i : v2)
		cout << i << ", ";
}