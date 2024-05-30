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
	// The data stored in the node
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
	void traverse();
	
	// Constructor
	List()
	{
		head = new Node<T>(T{});
	}
	
	// Destructor
	~List()
	{
		// The default destructor will call node A's destructor
		// Deleting node A's unique_ptr will call node B's destructor
		// Deleting node B's unique_ptr will call node C's destructor
		// ...
		// With long lists, these recursive calls can make the stack overflow 
		//
		// Overwrite node A with node B
		// This will release A's unique_ptr
		// Node A will now own B's unique_ptr
		// Overwrite node A with node C
		// This will release A's unique_ptr (which used to be B's unique_ptr)
		// Node A will now own C's unique_ptr
		//
		auto current = std::move(head->next);
		while (current) {
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
	while (node->next != nullptr) {
		std::cout << node->data << ",";
		// Move to the next node
		prev = node;
		node = node->next.get();
    }
	
	// Display the back element
	std::cout << node->data;
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

int main()
{
	List<int> list;
	
	for (int i = 0; i < 10; ++i) {
		list.push_back(i+1);
	}
	
	std::cout << "List elements: ";
	list.traverse();
	std::cout << '\n';
	
	std::cout << "Done\n";
}