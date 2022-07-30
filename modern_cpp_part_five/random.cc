#include <iostream>
#include <random>

using namespace std;

int main() {
	mt19937 mt;                                         // Create engine instance

	cout << "10 random integers between 0 and 100:" << endl;
	uniform_int_distribution<int> uid(0, 100);          // We want ints in the range 0 to 100

	for (int i = 0; i < 10; ++i ) {                     // Get 10 random numbers
		cout << uid(mt) << ", ";                        // Call the functor to get the next number
	}
	
	cout << endl << endl;

	cout << "10 random floating-point numbers between 0 and 1:" << endl;	
	uniform_real_distribution<double> did(0, 1);        // Doubles in the range 0 to 1

	for (int i = 0; i < 10; ++i ) {                     // Get 10 random numbers
		cout << did(mt) << ", ";
	}
}