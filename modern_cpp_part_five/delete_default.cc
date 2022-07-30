#include <utility>

class test {
	public:
		test(const test&) = delete;
		test& operator =(const test&) = delete;
		test(test&&) noexcept = default;
		test& operator=(test&&) noexcept = default;
		
		// We can also default the constructor
		test() = default;
};

int main() {
	test t1, t2, t3;
	//test t4(t1);
	//t2 = t1;
	//test t4(std::move(t1));
	t2 = std::move(t1);
}