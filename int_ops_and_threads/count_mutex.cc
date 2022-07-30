#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

mutex m;
int counter {0};

void task() {
    for (int i = 0; i < 100'000; ++i) {
		lock_guard<mutex> lg(m);
        ++counter;
	}
}

int main() {
    vector<thread> tasks;
    for (int i = 0; i < 10; ++i)
        tasks.push_back(thread{task});
    for (auto& t: tasks)
		t.join();
    cout << counter << endl;
}
