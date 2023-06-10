// Dining philosophers problem (part 3)
//
// 5 philosophers sit at a round table which has 5 forks on it.
// A philosopher has a fork at each side of them.
// A philosopher can only eat if they can pick up both forks.
// If a philosopher picks up the fork on their right,
// that prevents the next philosopher from picking up their left fork.
//
// All the philosophers pick up their left fork at the same time
// They wait to pick up their right fork (which is also their neighbour's left fork)
// If a philosopher cannot pick up the right fork, they put down the left fork
// and go back to thinking.
//
// If all the philosophers pick up their left fork at the same time,
// and put it down at the same time, they will still not be able to eat.
// Livelock
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>

using namespace std::literals;

// Some data about the problem
constexpr int nforks = 5;
constexpr int nphilosophers = nforks;
std::string names[nphilosophers] ={"A", "B", "C", "D", "E"};

// Keep track of how many times a philosopher is able to eat
int mouthfuls[nphilosophers] ={0};

// A philosopher who has not picked up both forks is thinking
constexpr auto think_time = 2s;

// A philosopher has picked up both forks is eating
constexpr auto eat_time = 1s;

// A philosopher who has picked up one fork will put it down again
// if they cannot pick up the other fork they need
constexpr auto time_out = think_time;

// A mutex prevents more than one philosopher picking up the same fork
// A philosopher thread can only pick up a fork if it can lock the corresponding mutex
std::mutex fork_mutex[nforks];

// Mutex to protect output
std::mutex print_mutex;

// Functions to display information about the 'nth' philosopher

// Interactions with a fork
void print(int n, const std::string& str, int forkno)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << "Philosopher " << names[n] << str << forkno << '\n';
}

// The philosopher's state
void print(int n, const std::string& str)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << "Philosopher " << names[n] << str << '\n';
}

// Thread which represents a dining philosopher
void dine(int phil_no)
{
	// Philosopher A has fork 0 on their left
	// and fork 1 on their right
	// Philosopher B has fork 1 on their left
	// and fork 2 on their right
	// ...
	// Philosopher E has fork 4 on their left
	// and fork 0 on their right
	//
	// Each philosopher must pick up their left fork first
	int lfork = phil_no;
	int rfork = (phil_no+1) % nforks;

	print(phil_no, "\'s left fork is number ", lfork);
	print(phil_no, "\'s right fork is number ", rfork);
	print(phil_no, " is thinking...");

	std::this_thread::sleep_for(think_time);

	// Make an attempt to eat
	print(phil_no, " reaches for fork number ", lfork);

	// Try to pick up the left fork
	bool locked = false;

	while (!locked) {
		fork_mutex[lfork].lock();
		print(phil_no, " picks up fork ", lfork);
		print(phil_no, " is thinking...");

		// Succeeded - now try to pick up the right fork
		std::this_thread::sleep_for(think_time);
		print(phil_no, " reaches for fork number ", rfork);

		locked = fork_mutex[rfork].try_lock();

		if (!locked) {
			print(phil_no, " puts down fork ", lfork);
			std::this_thread::sleep_for(think_time);
			fork_mutex[lfork].unlock();
		}
	}

	// Succeeded - this philosopher can now eat
	print(phil_no, " picks up fork ", rfork);
	print(phil_no, " is eating...");
	++mouthfuls[phil_no];

	std::this_thread::sleep_for(eat_time);

	print(phil_no, " puts down fork ", lfork);
	print(phil_no, " puts down fork ", rfork);
	print(phil_no, " is thinking...");

	fork_mutex[lfork].unlock();
	fork_mutex[rfork].unlock();
	std::this_thread::sleep_for(think_time);
}

int main()
{
	// Start a separate thread for each philosopher
	std::vector<std::thread> philos;

	for (int i = 0; i < nphilosophers; ++i) {
		philos.push_back(std::move(std::thread{dine, i}));
	}

	for (auto& philo: philos)
		philo.join();

	// How many times were the philosophers able to eat?
	for (int i = 0; i < nphilosophers; ++i) {
		std::cout << "Philosopher " << names[i];
		std::cout << " had " << mouthfuls[i] << " mouthful(s)\n";
	}
}