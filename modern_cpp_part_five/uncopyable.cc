#include <utility>

class test {
private:
    test(const test&);
    test& operator =(const test&);
public:
    test() {}
};

int main() {
	test t1, t2;
	//test t3(t1);
	t2 = t1;
}