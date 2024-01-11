// Broken implementation of lock-free queue (has data race)
#include <vector>
#include <list>
#include <thread>
#include <iostream>

template <typename T>
struct LockFreeQueue {
private:
	// Use an std::list to store the elements
	std::list<T> lst;

	// iHead and iTail iterators
	typename std::list<T>::iterator iHead, iTail;

public:
	// Class constructor
	LockFreeQueue()
	{
		// Create a "dummy" element to separate iHead from iTail
		lst.push_back(T());
		iHead = lst.begin();
		iTail = lst.end();
	}

	// Producer thread function
	void Produce(const T& t)
	{
		// Add the new element
		lst.push_back(t);

		// Update iTail
		iTail = lst.end();

		// Erase the removed elements
		lst.erase(lst.begin(), iHead);
	}

	// Consumer thread function
	bool Consume(T& t)
	{
		// Go to the first element
		auto iFirst = iHead;
		++iFirst;

		// If queue is not empty
		if (iFirst != iTail) {
			// Update iHead
			iHead = iFirst;

			// Fetch this first element
			t = *iHead;
			return true;
		}

		// No elements to fetch
		return false;
	}

	// Function to display all the elements
	void Print()
	{
		// Go to the first element
		auto head = iHead;
		++head;

		// We cannot use a range-for loop, because we only access some of the elements
		for (auto el = head; el != iTail; ++el)
			std::cout << *el << ", ";
		std::cout << '\n';
	}
}; // End of class definition

int main()
{
	LockFreeQueue<int> lfq;
	std::vector<std::thread> threads;
	int j = 1;

	for (int i = 0; i < 10; ++i) {
		// Run the member functions of LockFreeQueue in threads
		// Syntax for member function with std::thread:
		// First argument is a pointer to the member function
		// Second argument is the address of the object the member function is called on
		// (this will be the "this" pointer in the member function)
		// Then the arguments to the member function. These are passed as reference to int
		// so we need to wrap them in std::ref()
		/*
		lfq.Produce(i);
		lfq.Consume(j);
		*/

		std::thread produce(&LockFreeQueue<int>::Produce, &lfq, std::ref(i));
		threads.push_back(std::move(produce));
		std::thread consume(&LockFreeQueue<int>::Consume, &lfq, std::ref(j));
		threads.push_back(std::move(consume));
	}

	// Wait for the threads to complete
	for (auto& thr: threads)
		thr.join();

	lfq.Print();
}