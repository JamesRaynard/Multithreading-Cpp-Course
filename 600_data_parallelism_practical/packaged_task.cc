// packaged_task.cc
// Example of data parallelism using std::packaged_task
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <future>
#include <random>

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

// Compute the sum of a range of elements
double accum(double *beg, double *end) {
    return std::accumulate(beg, end, 0.0);
}

// Divide the data into 4 parts
// Use a separate part to process each subset
double add_parallel(std::vector<double>& vec)
{
	// Type alias to simplify the code	
	using task_type = double(double *, double *);

	// Packaged tasks to manage each thread
	std::packaged_task<task_type> ptask1(accum);
	std::packaged_task<task_type> ptask2(accum);
	std::packaged_task<task_type> ptask3(accum);
	std::packaged_task<task_type> ptask4(accum);
	
	// Future objects for each thread's result
	auto fut1 = ptask1.get_future();
	auto fut2 = ptask2.get_future();
	auto fut3 = ptask3.get_future();
	auto fut4 = ptask4.get_future();
	
	// Find the first element of the vector
	auto vec0 = &vec[0];
	
	// Find the number of elements
	auto vsize = vec.size();
	
	// Start the threads
	// Pass the subset's range as argument to the task function
	std::thread thr1(std::move(ptask1), vec0, vec0 + vsize/4);
	std::thread thr2(std::move(ptask2), vec0 + vsize/4, vec0 + 2*vsize/4);
	std::thread thr3(std::move(ptask3), vec0 + 2*vsize/4, vec0 + 3*vsize/4);
	std::thread thr4(std::move(ptask4), vec0 + 3*vsize/4, vec0 + vsize);
	
	thr1.join(); thr2.join(); thr3.join(); thr4.join();
	
	// Reduce step
	// Combine the results for each subset
	return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

int main() {
	// Populate a vector with elements 1, 2, ..., 16
	std::vector<double> vec(16);
	std::iota(vec.begin(), vec.end(), 1.0);
	
	// Populate a vector with 10,000 random elements
	std::vector<double> vrand(10'000);
	std::generate(vrand.begin(), vrand.end(),
		[&vrand]() { return dist(mt); });
	
	// Do the calculations 
	std::cout << "Sum of first 16 integers: " << add_parallel(vec) << '\n';
	std::cout << "Sum of 10,000 random numbers: " << add_parallel(vrand) << '\n';
}