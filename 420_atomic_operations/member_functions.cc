// Demonstrate member functions of atomic types
#include <iostream>
#include <atomic>

int main()
{
	std::atomic<int> x = 0;
	std::cout << "After initialization: x = " << x << '\n';
	
	// Atomic assignment to x
	x = 2;
	
	// Atomic assignment from x. y can be non-atomic
	int y = x;
	
	std::cout << "After assignment: x = " << x << ", y = " << y << '\n';
	
	x.store(3);
	std::cout << "After store: x = " << x.load() << '\n';
	
	std::cout << "Exchange returns " << x.exchange(y) << '\n';
	std::cout << "After exchange: x = " << x << ", y = " << y << '\n';
}
