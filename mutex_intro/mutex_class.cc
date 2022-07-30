#include <thread>
#include <mutex>
#include <vector>	
#include <iostream>

using namespace std;

class Vector {
	mutex m;
	vector<int> v;
public:
	void push_back(const int& i) {
		m.lock();
		v.push_back(i);
		m.unlock();
	}
	void print() {
		for (auto i : v) {
			cout << i << ", ";
		}
	}
};

//Vector vec;
vector<int> vec;

void func() {
	for (int i = 0; i < 5; ++i) {
		vec.push_back(i);
		std::this_thread::sleep_for(50ms);
	}
}

int main() {
	vector<std::thread> threads;
	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread{ func });
	for (auto& t: threads)
		t.join();
	//vec.print();
	cout << vec.size();
	for (auto i : vec)
		cout << i << ", ";
}