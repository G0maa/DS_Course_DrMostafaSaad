// This time I focused on the code being DRY and on complexity I guess, so it took a bit more time I think.

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
	Node* prev { };	 // Previous node!

	Node(int data) : data(data) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}

	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;

	// let's maintain how many nodes

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

	void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}

		if (node->prev == nullptr)
			cout << "X\t";
		else
			cout << node->prev->data << "\t";

		cout << " <= [" <<node->data << "]\t => \t";

		if (node->next == nullptr)
			cout << "X\t";
		else
			cout << node->next->data << "\t";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}

	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node* cur = head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		} else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++) {
			if (len == length-1)	// make sure we end at tail
				assert(cur == tail);
		}

		assert(length == len);
		assert(length == (int )debug_data.size());

		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length-1)	// make sure we end at head
				assert(cur == head);
		}
		cout << "\n";
	}
	////////////////////////////////////////////////////////////

	Node* insert_inbetween(Node* prev, Node* new_member) {
		if(prev == nullptr) {
			link(new_member, head);
			head = new_member;
			return head->next;
		}
		else {
			Node* after = prev->next;
			link(prev, new_member);
			link(new_member, after);
			return after;
		}
	}

	void merge_2sorted_lists(LinkedList &other) { // O(n+m) time, O(1) memory.. Different implementation from Doctor's.
		if(!other.length) // Doctor created a new node and linked everything with it.
			return;
		else if(!length) {
			head = other.head, tail = other.tail;
			length = other.length;
			return;
		}

		Node* cur_this = head, *cur_other = other.head, *temp;
		while(cur_this && cur_other) {
			if(cur_other->data <= cur_this->data) {
				temp = cur_other; // no prev from nullptr : )
				cur_other = cur_other -> next;
				cur_this = insert_inbetween(cur_this->prev, temp); 
			}
			else
				cur_this = cur_this -> next;
		}

		if(cur_this == nullptr && cur_other != nullptr) {
			link(tail, cur_other);
			tail = other.tail;
		}

		other.head = other.tail = nullptr;
		length += other.length;
		other.length = 0;
	}

	void reverse() { // O(n) time, O(1) memory
		if(head == nullptr || head -> next == nullptr)
			return;
		
		for(Node* cur = head; cur; cur = cur->prev)
			swap(cur->next, cur->prev);

		swap(head, tail);
	}


	void swap_fw2(int k) { // O(k) time, O(1) memory... very little changes.
		if(head == nullptr || head -> next == nullptr) // here
			return;

		int temp = k - 1;
		bool flag = false; //here
		Node *f = head, *b = tail, *bf, *ab, *af, *bb; // Revise when k * 2 > length as in the other solution.
		while(temp--) {
			f = f->next, b = b->prev;
			if(f == b || f->next == b)
				break;
		}
			
		while(temp-- && temp > 0) {
			f = f->prev, b = b->next;
			if(f == nullptr || b == nullptr)
				return;
		}
		if(f == b) // here
			return;
		if(f == head && b == tail) {
			swap(head, tail);
		}
		if(f->next == b || b->next == f) // here
			flag = true;

		af = f->next, bf = f->prev;
		ab = b->next, bb = b->prev;
		
		link(bf, b), link(f, ab);
		if(flag) // here
			link(b, f);
		else
			link(b, af), link(bb, f);
	}

	void swap_fw1(int k) { // O(k) time, O(1) memory.
		if(k <= 0)
			return;
		if(k > length)
			k %= length;
		
		if(k * 2 > length) // This deals when they're the same node.
			k = length - k + 1;

		// if(k == 1) { // This is all useless
		// 	if(length > 2) {
		// 		Node *ahead = head -> next, *btail = tail -> prev;
		// 		link(btail, head);
		// 		link(tail, ahead);
		// 		head->next = nullptr;
		// 		tail->prev = nullptr;
		// 		swap(head, tail);
		// 	}
		// 	else {
		// 		tail->next = head;
		// 		head->prev = tail;
		// 		tail->prev = nullptr;
		// 		head->next = nullptr;
		// 		swap(head, tail);
		// 	}
		// }
		// else {
			int temp = k - 1; // I tried to DRY as much as I could.
			Node *f = head, *b = tail, *bf, *ab, *af, *bb;
			while(temp--) { // I think better than getnth().
				f = f->next, b = b->prev;
			}

			af = f->next, bf = f->prev;
			ab = b->next, bb = b->prev;
			
			link(bf, b);
			link(f, ab);
			if(k * 2 == length) {
				link(b, f);
			}
			else {
				link(b, af);
				link(bb, f);
			}
			if(k == 1)
				swap(head, tail);
		// }
	}

	Node* find_the_middle2() { // O(n) time, O(n) memory, AND WRONG IDEA.
		if(!head) // Prof used fast & slow pointers, where one moves one step and the other moves 2 steps.
			return nullptr;
		
		vector<Node*> not_correct;
		for(Node* cur = head; cur; cur = cur -> next)
			not_correct.push_back(cur);

		return not_correct[((int)not_correct.size() / 2)];
	}

	Node* find_the_middle1() { // O(n/2) time, o(1) memory, I returned pointer cuz I felt it's just more convenient.
		if(length <= 1) // Same solution as prof... finally?
			return head;
		
		Node *cur_head = head, *cur_tail = tail;
		while(cur_head != cur_tail && cur_head -> prev != cur_tail) {
			cur_head = cur_head -> next;
			cur_tail = cur_tail -> prev;
		}
		return cur_head;
	}

	bool is_palindrome() { // O(n/2) time, o(1) memory
		if(length <= 1)
			return true;

		// Doctor used length variable and divided it by 2... I think no big difference here (finally :) )
		Node *cur_head = head, *cur_tail = tail;
		while(cur_head != cur_tail && cur_head -> prev != cur_tail) {
			if(cur_head -> data != cur_tail -> data)
				return false;
			cur_head = cur_head -> next;
			cur_tail = cur_tail -> prev;
		}
		return true;
	}

	void delete_odd_positions() { // O(n) time, o(1) memory
		if(!head)
			return;
		// Doctor yet again used dummy node idea... :c
		delete_front(); // big brain move right there :D
		delete_even_positions();
	}

	void delete_even_positions() { // O(n) time, o(1) memory
		if(!head)
			return;
		// I geuss doctor's code is just cleaner?
		for(Node* cur = head -> next; cur; ) {
			cur = delete_and_link(cur);
			if(cur -> next == nullptr || cur -> next -> next == nullptr)
				break;
			cur = cur -> next -> next;
		}
	}

	void delete_all_nodes_with_key(int value) { // O(n) time, o(1) memory.
		if(!length) // forgot about this one :)
			return;
		
		// Doctor used a dummy node (حسيتها مش مستاهلة), or basically he made the function based on the current functions,
		// I changed the functions to fit my idea. قولب الكود على الفانكشن.. قولب الفانكشن على الكود.
		for(Node* cur = head; cur;) {
			if(cur -> data == value)
				cur = delete_and_link(cur); // updated this function.
			if(cur == nullptr)
				cur = head;
			else
				cur = cur -> next;
		}
	}

	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}

	void link(Node* first, Node*second) {
		if(first)
			first->next = second;
		if(second)
			second->prev = first;
	}

	void insert_end(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else {
			link(tail, item);
			tail = item;
		}
		debug_verify_data_integrity();
	}

	void insert_front(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else {
			link(item, head);
			head = item;
		}
		debug_verify_data_integrity();
	}

	void print_reversed()  {
		for (Node* cur = tail; cur; cur = cur->prev)
			cout << cur->data << " ";
		cout << "\n";
	}

	void delete_front() {
		if(!head)
			return;
		Node* cur = head->next;
		delete_node(head);
		head = cur;

		// Integrity change
		if(head)
			head->prev = nullptr;
		else if(!length)
			tail = nullptr;

		debug_verify_data_integrity();
	}

	void delete_end() {
		if(!head)
			return;
		Node* cur = tail->prev;
		delete_node(tail);
		tail = cur;

		// Integrity change
		if(tail)
			tail->next = nullptr;
		else if(!length)
			head = nullptr;

		debug_verify_data_integrity();
	}

	Node* delete_and_link(Node* cur) {
		// remove this node, but connect its neighbors
		if(cur == head) { // added part by me.
			delete_front();
			return nullptr; // no prev node.
		}
		else if(cur == tail) {
			delete_end();
			return tail;
		}	
		else {
			Node* ret = cur->prev;
			link(cur->prev, cur->next);
			delete_node(cur);
			return ret;
		}
	}

	void delete_node_with_key(int value) {
		if (!length)
			return;
		if (head->data == value)
			delete_front();
		else {
			for (Node *cur = head; cur; cur = cur->next) {
				if (cur->data == value) {
					cur = delete_and_link(cur);
					if (!cur->next)	// we removed last node!
						tail = cur;
					break;
				}
			}
		}
		debug_verify_data_integrity();
	}

	void embed_after(Node* node_before, int value) {
		// Add a node with value between node and its next
		Node* middle= new Node(value);
		++length;
		debug_add_node(middle);

		Node* node_after = node_before->next;
		link(node_before, middle);
		link(middle, node_after);
	}

	void insert_sorted(int value) {		// O(n) time - O(1) memory
		// 3 special cases for simplicity
		if (!length || value <= head->data)
			insert_front(value);
		else if (tail->data <= value)
			insert_end(value);
		else {
			// Find the node I am less than. Then I am before it
			for (Node *cur = head; cur; cur = cur->next) {
				if (value <= cur->data) {
					embed_after(cur->prev, value);
					break;
				}
			}
		}
		debug_verify_data_integrity();

		// This idea is used in Insertion Sort Algorithm
	}
};

void test1() {
	cout << "\n\ntest1\n";
	LinkedList list;

	list.insert_end(3);
	list.insert_end(5);
	list.insert_end(7);
	list.insert_front(7);
	list.delete_front();
	list.delete_end();
	list.insert_sorted(2);
	list.insert_sorted(9);
	list.insert_sorted(7);
	list.insert_sorted(4);
	list.insert_sorted(1);
	list.delete_node_with_key(7);

	list.print();
	//list.print_reversed();

	string expected = "1 2 3 4 5 9";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

void test2() {
	cout << "\n\ntest2\n";
	LinkedList list;

	list.insert_end(3);
	list.insert_end(5);
	list.insert_end(7);
	list.insert_front(7);
	list.delete_front();
	list.delete_end();
	list.insert_sorted(2);
	list.insert_sorted(9);
	list.insert_sorted(7);
	list.insert_sorted(4);
	list.insert_sorted(1);
	list.delete_node_with_key(9);

	list.print();
	list.print_reversed();

	string expected = "1 2 3 4 5 7";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}


int main() {
	// test1();
	// test2();
	//test3();

	LinkedList test;
	test.insert_end(1);
	test.insert_end(2);
	test.insert_end(3);
	test.insert_end(4);
	// test.insert_end(5);
	// test.insert_end(6);

	// LinkedList test2;
	// test2.insert_end(1);
	// test2.insert_end(30);
	// test2.insert_end(22);
	// test2.insert_end(24);
	// test2.insert_end(35);
	
	// cout << "\n\n" << test.find_the_middle2() -> data << "\n\n";
	// test.print();
	test.swap_fw2(1);
	// if(test.is_palindrome()) {
	// 	cout << "\n\nYES\n\n";
	// }
	// else {
	// 	cout << "\n\nNO\n\n";
	// }
	test.print();

	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

