#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>

using namespace std;
using namespace std::execution;

int main() {
	vector<int> v(2000);
	int count {0};
	for_each(v.begin(), v.end(), [&] (int& x) { x = ++count; });                   // v -> {1, 2, ..., 2000}
	for_each(seq, v.begin(), v.end(), [&] (int& x) { x = ++count; });
}