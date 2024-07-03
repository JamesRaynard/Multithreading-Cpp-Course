// Simple linked list implementation
// Uses std::unique_ptr
// Not thread safe without external synchronization
#include <iostream>
#include <memory>

// The list consists of a linked series of "nodes"

// Each element is a "node". It has a data member
// and a pointer to the next node in the list
template <typename T>
struct Node {
	// The data stored in the next
	T data;
	
	// The pointer to the next node
	std::unique_ptr<Node> next{nullptr};
	
	// Constructor
	Node(T data) : data(data) {}
	
	// Delete the copy and move operators
	Node(const Node&) = delete;
	Node& operator =(const Node&) = delete;
	Node(Node&&) = delete;
	Node& operator =(Node&&) = delete;
};

template <typename T>
class List {
	// Non-owning pointer to the first node
	// (This node does not own any data)
	Node<T> *head;

  public:	
	// Operations
	void push_back(T arg);
	void erase_first();
	void erase(Node<T> *node);
	void traverse();
	
	// Constructor
	List()
	{
		head = new Node<T>(T{});
	}
	
	// Destructor
	~List()
	{
		// Deleting head will call its unique_ptr's destructor
		// This destructor will destroy the first node
		// Destroying the first node's unique_ptr will call the second node's destructor
		// The second node's destructor will call unique_ptr's destructor
		// ...
		// Instead, we overwrite the head with each element in turn
		
		// Get the first element
		Node<T> *node = head->next.get();
		
		while (current) {
			// Equivalent to current.reset(current->next.release()));
			current = std::move(current->next);
		}
		
		delete head;
	}
};

template <typename T>
void List<T>::traverse()
{
	if (head->next == nullptr) {
		std::cout << "Empty list\n";
		return;
	}
	// Get the front element
	Node<T> *prev = head;
	
	// Get the second element
	Node<T> *node = prev->next.get();
	
	// Iterate over the nodes until we reach the back
	while (node != nullptr) {
		std::cout << node->data << ",";
			// Move to the next node
			prev = node;
			node = node->next.get();
	}
}

template <typename T>
void List<T>::push_back(T arg)
{
	// Find the back of the list
	// Get the front element
	Node<T> *prev = head;
	
	// Get the second element
	Node<T> *node = prev->next.get();
	
	// Iterate over the nodes until we reach the back		
	while (node != nullptr) {
		// Move to the next node
		prev = node;
		node = node->next.get();
	}

	// Create the new node
	auto new_node = std::make_unique<Node<T>>(arg);
	
	// Make this node the new last element	
	// Set the last-but-one node to point to it
	prev->next = std::move(new_node);
}

template <typename T>
void List<T>::erase_first()
{
	List<T>::erase(head->next.get());
}

template <typename T>
void List<T>::erase(Node<T> *del_node)
{
	// Find the predecessor to del_node
	
	// Get the front element
	Node<T> *prev = head;
	
	// Get the second element
	Node<T> *node = prev->next.get();
	
	// Iterate over the nodes until we reach the predecessor		
	while (node != del_node) {
		// Move to the next node
		prev = node;
		node = node->next.get();
	}
	
	prev->next = std::move(del_node->next);
	del_node = nullptr;	
}

int main()
{
	List<int> list;
	
	for (int i = 0; i < 10; ++i) {
		list.push_back(i+1);
	}
	
	std::cout << "List elements: ";
	list.traverse();
	std::cout << '\n';
	
	list.erase_first();
	
	std::cout << "List elements: ";
	list.traverse();
	std::cout << '\n';
	
	std::cout << "Done\n";
}
