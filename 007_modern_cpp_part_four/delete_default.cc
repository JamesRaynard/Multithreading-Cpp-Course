// Example of a class with defaulted and deleted operators
#include <utility>

// Move-only class
class Test {
	public:
		// =delete means the function exists but cannot be called
		// In older C++, we had to declare the member function private
		Test(const Test&) = delete;
		Test& operator =(const Test&) = delete;
		
		// =default means the compiler will synthesize
		// the default version of the operator
		Test(Test&&) noexcept = default;
		Test& operator=(Test&&) noexcept = default;
		
		Test() = default;
};

int main()
{
	Test test1, test2, test3;
	//Test test4(test1);
	//test2 = test1;
	Test test4(std::move(test1));
	test3 = std::move(test2);
}