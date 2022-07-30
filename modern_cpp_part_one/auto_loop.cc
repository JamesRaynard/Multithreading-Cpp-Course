#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v{4, 2, 3, 5, 1};
	
	for (auto it = v.begin(); it != v.end(); ++it)
		*it += 2;
	
	cout << "Vector elements: ";
	for (auto it = v.begin(); it != v.end(); ++it)
		cout << *it << ", ";
}