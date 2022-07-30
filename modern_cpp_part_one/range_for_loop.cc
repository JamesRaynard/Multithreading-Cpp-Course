#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v{4, 2, 3, 5, 1};
	
	for (auto& i : v)
		i += 2;
	
	cout << "Vector elements: ";
	for (auto i : v)
		cout << i << ", ";
}