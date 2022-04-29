#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data { };
	Node* next { };
	Node(int data) : data(data) {}
	~Node() {
		cout << "Destroy value: " << data <<" at address "<< this<< "\n";
	}
};

class LinkedList {
private:
	Node *head { };

	vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:

	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;

	~LinkedList() { // O(n) time O(1) memory
		Node* last_cur;
		for(Node *cur = head; cur;) {
			last_cur = cur;
			cur = cur -> next;
			delete last_cur;
		}
		// delete head, tail, length;
	}

	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	void insert_front(int val) { // O(1) time O(1) space
		Node* new_node = new Node(val);
		new_node->next = head;
		head = new_node;
	}

	Node* get_tail() { // time O(n) space o(1)
	
		if(!head) // forgot this one
			return nullptr;

		Node* tail = head;
		while(tail -> next != nullptr) {
			tail = tail -> next;
		}
		return tail;
	}
};


int main() {
	// test1();
	// test2();
	//test3();


	
	LinkedList test;
	LinkedList test2;
	// for(int i = 0; i < 5; i++)
	// 	test.insert_front(1);

	// for(int i = 0; i < 5; i++)
		// test2.insert_front(i);
	// test.insert_end(1);
	// test.~LinkedList();
	// test.print();
	// test.delete_front();
	// if(test.is_same(test2))
		// cout << "YES";
	// else
		// cout << "NO";
	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

