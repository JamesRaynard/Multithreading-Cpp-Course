#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int x{7};                                         // Equivalent to int x = 7;
	string s{"Let us begin"};                         // Equivalent to string s("Let us begin");
	
	cout << "x = " << x << endl;
	cout << "s = \"" << s << "\"" << endl;
	
	// Narrowing conversions are not allowed
	int y = 7.7;                                      // Legal, although compilers may warn
	//int y{7.7};                                     // Illegal
	cout << "y = " << y << endl;
	
	// Can  be used with multiple initial values
	vector<int> v{4, 2, 3, 5, 1};                    // std::vector variable with elements 4, 2, 3, 5, 1
	string hello{'H', 'e', 'l', 'l', 'o'};            // std::string variable with data "Hello"
	
	cout << "v = ";
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << ", ";
	
	cout << endl << "hello = \"" << hello << "\"" << endl;
}