// Examples of lambda expression with lambda-local variables
#include <iostream>

int main()
{
	// y is local to the lambda body
	auto add_two = [y = 2] (int x) {
		return x + y;
	};
	
	std::cout << "Calling add_two(2) gives " << add_two(2) << '\n';
	std::cout << "Calling add_two(5) gives " << add_two(5) << '\n';
	
	// z is a local variable in the containing scope of the lambda
	int z = 1;
	
	// y1 is local to the lambda body
	// It is initialized using the local variable z
	auto add_z_plus1 = [y = z + 1](int x){
		return x + y;
	};
	
	std::cout << "Calling add_z_plus1(2) gives " << add_z_plus1(2) << '\n';
	std::cout << "Calling add_z_plus1(5) gives " << add_z_plus1(5) << '\n';
}