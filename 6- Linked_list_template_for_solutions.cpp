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

// Somethings I didn't focus much on:
// O(something) in time and space -> not as much efficient as it shoould code.
// code isn't really clean.
// dr's codes are not 101% understood, I get the idea, but as long as I solved the problem I give them like 1/2 the focus needed.
// I think I should have dealt with the given problems in a more problem-solvey fation, which I think would have led to eliminating of what's above.
// Hope that didn't screw up the learning journey : )

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;	// let's maintain how many nodes

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
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

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
		cout << "************\n"<<flush;
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
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?
		assert(length == len);
		assert(length == (int)debug_data.size());
	}

	////////////////////////////////////////////////////////////

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

	void insert_end(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else
			tail->next = item, tail = item;
	}

	////////////////////////////////////////////////////////////

	void reverse_chains(int k) { // O(n) Time, O(1) Memroy.
		if(k > length || k <= 1)
			return;
		else if(k == length)
			reverse();
		else {
			Node *brev = nullptr, *arev, *shead, *stail, *bcur, *cur, *acur;
			int t = length / k;
			while(t--) {
				if(brev == nullptr)
					shead = head;
				else
					shead = brev -> next;

				bcur = shead;
				cur = bcur -> next;
				acur = cur -> next;

				int c = k - 1;
				while(c--) {
					cur -> next = bcur;
					bcur = cur;
					cur = acur;
					if(acur != nullptr)
						acur = acur -> next;
				}
				stail = bcur;

				if(shead == head)
					head = stail;
				if(stail == tail)
					tail = shead;
				arev = cur;
				shead -> next = arev;
				if(brev != nullptr)
					brev -> next = stail;

				brev = shead;
				// this->print();
			}
		}
	}

	void delete_repeated() { // clean & rervise. O(n) time, O(1) memory... I guess I can't get better eh?
		if(length <= 1) // Added a dummy node.
			return;

		Node *prev = nullptr;
		for(Node* cur = head; cur -> next != nullptr;) {
			if(cur -> data == cur -> next -> data) {
				int key = cur -> data;
				if(prev != nullptr) {
					while(prev -> next -> data == key) {
						delete_using_prev(prev); 
						if(prev == tail)
							break;
					}
				}
				else {
					while(head -> data == key) {
						delete_front();
						if(head == nullptr)
							break;
					}
				}
				if(prev == nullptr)
					cur = head;
				else
					cur = prev -> next;
				if(cur == nullptr) // DRY
					break;
			}
			else {
				prev = cur;
				cur = cur -> next;
			}
		}
	}

	void add_num(LinkedList &another) { // Memory O(1), Time O(n) (where n depends on carry existance) I think generally n for shorter list.
		Node *cur_this = head, *cur_another = another.head, *prev_this;
		int carry = 0; // traversed with if conidtion if there any node existing.
		while(cur_another != nullptr && cur_this != nullptr) {
			carry += cur_this->data + cur_another ->data;
			cur_this -> data = carry % 10;
			carry /= 10;
			prev_this = cur_this;
			cur_another = cur_another -> next, cur_this = cur_this -> next;
		}

		if(cur_another == nullptr && cur_this == nullptr) { // again... not clean.
			if(carry != 0) // I think although doctor's code is cleaner, my code is somewhat more efficient, doctors code traverses through all elements although there might not be a carry.
				insert_end(carry);
			return;
		}
		else if(cur_another == nullptr && cur_this != nullptr) {
			if(carry != 0)
				carry_dry(cur_this, carry);
		}
		else {
			prev_this -> next = cur_another;
			tail = another.tail;
			if(carry != 0)
				carry_dry(cur_another, carry);
		}
	}

	void carry_dry(Node* cur, int carry) {
		while(cur != nullptr) {
			carry += cur ->data;
			cur->data = carry % 10;
			carry /= 10;
			cur = cur -> next;
		}
		if(carry != 0)
			insert_end(carry);
	}

	void insert_alternate(LinkedList &another) { // O(1) Memory - O(N) Time (where N is the shortest list)
		Node *cur_this = head, *cur_another = another.head, *temp;
		length += another.length; // similar, but less if-conditions at the end
		if(cur_another == nullptr)
			return;
		else if(cur_this == nullptr) {
			head = another.head;
			tail = another.tail;
			// forgot to update length.
			return;
		}

		while(cur_another -> next != nullptr && cur_this -> next != nullptr) {
			temp = cur_another -> next;
			cur_another -> next = cur_this -> next;
			cur_this -> next = cur_another;

			cur_another = temp;
			cur_this = cur_this -> next -> next;
		}

		if(cur_this == nullptr && cur_another == nullptr) { // complex? spaghitti? I guess.
			cur_this -> next = cur_another;
			tail = cur_another;
		}
		else if(cur_this -> next == nullptr && cur_another -> next != nullptr) {
			cur_this -> next = cur_another;
			tail = another.tail;
		}
		else {
			cur_another -> next = cur_this -> next;
			cur_this -> next = cur_another;
		}
		// forgot to update another.
	}

	void odd_pos_even_pos() { // this solution is O(2n) time and o(n) memory
		vector<Node*> odd, even; //  next next, and better complexity.
		bool is_even = 1;
		for(Node* cur = head -> next; cur; cur = cur -> next) {
			if(is_even)
				even.push_back(cur);
			else
				odd.push_back(cur);
			is_even = !is_even;
		}
		head -> next = odd[0];
		for(int i = 0; i < (int)(odd.size()) - 1; i++)
			odd[i] -> next = odd[i + 1];
		
		odd[(int)(odd.size()) - 1] -> next = even[0];

		for(int i = 0; i < (int)(even.size()) - 1; i++)
			even[i] -> next = even[i + 1];
		
		tail = even[(int)(even.size()) - 1];
		tail -> next = nullptr;
	}

	int max(Node* head = nullptr, bool is_first_call = true) {		// O(n) time - O(n) memory
		// It is tricky to have function name same as standard
		// use std for standard and this-> for the class for clarity
		if (is_first_call)
			return this->max(this->head, false);
		
		if(head == nullptr)
			return INT_MIN;

		return std::max(head->data, this->max(head->next, false));
		// I know how to do it recursion wise, but I didn't know how to do it in the a class funciton, didn't know how to call head inside here.
	}

	void move_to_back(int key) {
		if(length <= 1)
			return;
		int pos = 0;
		while(head -> data == key && pos < length) {
			left_rotate(1);
			pos++;
		}
		Node* prev = head;
		Node* cur = head -> next;
		while(pos < length - 1) {
			if(cur -> data == key) {
				connect_next(prev);
				change_tail(cur);
			}
			cur = prev -> next -> next;
			prev = prev -> next;
			pos++;
		}
	}

	void change_tail(Node* new_tail) {
		tail -> next = new_tail;
		new_tail -> next = nullptr;
		tail = new_tail;
		return;
	}

	void remove_last_occurance(int key) {
		if(length == 0)
			return;

		Node* prev = head;
		Node* prev_delete_this = nullptr;
		for(Node* cur = head -> next; cur;) {
			if(cur -> data == key) {
				prev_delete_this = prev;
			}
			prev = cur;
			cur = cur -> next;
		}

		if(head -> data == key && prev_delete_this == nullptr) {
			delete_front();
			return;
		}
		else if(prev_delete_this != nullptr)
			delete_using_prev(prev_delete_this);
	}

	void connect_next(Node* prev) {
		if(prev == tail)
			return;
		if(prev -> next == tail) {
			tail = prev;
			return;
		}
			
		Node* cur = prev -> next;
		prev -> next = cur -> next;
		return;
	}

	void delete_using_prev(Node* prev) {
		Node* delete_this;
		if(tail == prev -> next) {
			delete_this = prev -> next;
			tail = prev;
			tail -> next = nullptr;
			delete delete_this; // DRY
		}
		else {
			delete_this = prev -> next;
			connect_next(prev);
			delete delete_this;
		}
	}

	void delete_duplicates() {
		if(length <= 1)
			return;

		for(Node* cur = head; cur; cur = cur -> next) {
			Node* prev = cur;
			for(Node* is_delete = cur -> next; is_delete;) {
				if(is_delete -> data == cur -> data) {
					is_delete = is_delete -> next;
					delete_using_prev(prev);
				}
				else {
					prev = is_delete;
					is_delete = is_delete -> next;
				}
			}
		}
	}

	void left_rotate(int val) { // dr code is *much* simpler.
		if(length <= 1)
			return;

		int k = val % length;
		while(k--) {
			Node* new_tail = head;
			head = head -> next;
			tail -> next = new_tail;
			new_tail -> next = nullptr;
			tail = new_tail;
		}
	}

	void swap_head_tail() {
		if(length == 1)
			return;
		else if(length == 2) {
			tail -> next = head;
			head -> next = nullptr;
			swap(head, tail);
		}
		else {
			Node* prev = get_nth(length - 2);
			tail -> next = head -> next;
			head -> next = nullptr;
			prev -> next = head;
			swap(head, tail);
		}
		
	}

	void insert_sorted(int value) {
		if(length == 0 || value <= head -> data) // had what's after || in a separate else if *face_palm*
			insert_front(value);
		else if(value >= tail -> data)
			insert_end(value);
		else {
			int pos = 1;
			for(Node* cur = head; cur; cur = cur -> next) {
				if(value >= cur -> data && value <= cur -> next -> data) { // should have looped for first node that is <= myself.
					inesrt_nth(pos, value); // like this is o(2n), should have made a separate function for inserting when you have before_node already.
					break;
				}
				pos++;
			}
		}
		return;
	}

	void inesrt_nth(int pos, int value) { // zero-indexed
		if(pos == 0) {
			insert_front(value);
		}
		else if(pos == length - 1) {
			insert_end(value);
		}
		else {
			Node* new_node = new Node(value);
			Node* before_node = get_nth(pos - 1);
			new_node -> next = before_node -> next;
			before_node -> next = new_node;
			length++; // forgot this one : )
		}
		return;
	}

	void delete_even_positions() { // zero indexed.
		int pos = 1;
		Node* prev = head;
		Node* cur = head -> next;
		while(cur && prev) {
			cur = cur -> next;
			delete_using_prev(prev);
			if(cur == nullptr)
				return;
			prev = cur;
			cur = prev -> next;
		}
		return;
	}

	void reverse() {
		Node* before_cur = head;
		Node* cur = head -> next;
		Node* after_cur = head -> next -> next;

		while(after_cur) {
			cur -> next = before_cur;
			before_cur = cur;
			cur = after_cur;
			after_cur = after_cur -> next;
		}
		swap(head, tail);
		head -> next = before_cur;
		tail -> next = nullptr;
	}

	void swap_pairs() { // dr code much shorter
		Node* next_cur = head -> next;
		for(Node* cur = head; cur && next_cur; cur = cur -> next -> next) {
			swap(next_cur -> data, cur -> data);
			if(next_cur -> next == nullptr || cur -> next == nullptr)
				break;
			next_cur = next_cur -> next -> next;
		}
		return;
	}

	void delete_node_with_key(int value) {
		int index = search(value);
		if(index == -1)
			return;
		else if(index == 0) { 
			delete_front();
		}
		else if(index == length - 1) {
			delete_last();
		}
		else {
			delete_nth(index);
		}
		return;
	}

	int search(int val) {
        int index = 0;
        for(Node* cur = head; cur; cur = cur -> next) {
            if(cur->data == val) {
                return index;
            }
            index++;
        }
        return -1;
    }

	void delete_nth(int val) { // zero-indexed, O(n) time O(1) sapce, is this code okay?
		if(val < 0 || val >= length)
			return;

		if(val == 0) {
			delete_front();
			return;
		}

		if(val == length - 1) {
			delete_last();
			return;
		}
		
		Node* before_del = get_nth(val - 1);
		Node* delete_this = before_del -> next;
		before_del->next = delete_this->next;
		length--;
		delete delete_this;
	}

	void delete_last() { // O(n) time o(1) space

		if(length == 0) // dr code again shorter & better.
			return;

		if(length == 1) {
			delete head;
			tail = head = nullptr;
		}

		Node* new_tail = head; // dr used get_nth
		while(new_tail -> next -> next != nullptr) {
			new_tail = new_tail -> next;
		}
		delete new_tail->next;
		tail = new_tail;
		tail -> next = nullptr;
		length--;
	}

	void delete_front() { // O(1) both,
		if(length == 0) // if(head)
			return;
		Node* delete_this = head;
		head = head -> next;
		length--;
		delete delete_this;
		if(!head) // missed this one 
			tail = nullptr;
	}

	bool is_same(const LinkedList &list2) { // Memory O(1) Time(N) Dr code is much shorter :c
		Node* list2_head = list2.head;
		for(Node* cur = head; cur && list2_head;) {
			if(cur -> data == list2_head -> data) {
				if(cur -> next != nullptr && list2_head -> next != nullptr) {
 					cur = cur-> next;
					list2_head = list2_head -> next;
				}
				else if(cur -> next == nullptr && list2_head -> next == nullptr)
					return 1;
				else // this might be useless
					return 0;
			}
			else
				return 0;
		}
		return 0; // because of forloop condition.
	}

	bool is_same_with_length(const LinkedList &list2) { // Memory O(1) Time(N)
		if(list2.length != length)
			return 0;

		Node* list2_head = list2.head;
		for(Node* cur = head; cur && list2_head;) {
			if(cur -> data != list2_head -> data)
				return 0;
			
			cur = cur-> next;
			list2_head = list2_head -> next;
		}
		return 1;
	}

	Node* get_nth(int n) { // O(n) time O(1) memory

		if(n > length || n < 0) // 0-indexed
			return nullptr;

        int pos = 0;
        for(Node* cur = head; cur; cur = cur -> next) {
            if(pos == n) {
                return cur;
            }
            pos++;
        }
        return nullptr;
    }

	Node* get_nth_fromback(int val) {
		return get_nth(length - val);
	}

	void insert_front(int val) { // O(1) time O(1) space
		Node* new_node = new Node(val);
		new_node->next = head;
		head = new_node;
		length++;
		if(length == 1) // forgot this one.
			tail = head;
		// length++;
	}

	~LinkedList() { // O(n) time O(1) memory
		Node* last_cur;
		for(Node *cur = head; cur;) {
			last_cur = cur;
			cur = cur -> next;
			delete last_cur;
		}
		// delete head, tail, length;
	}
	bool check() {
		if(tail -> next == nullptr && tail -> data == 1)
			return 1;
		return 0;
	}
};

void test1() {
	cout << "\n\ntest1\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(6);
	list.reverse_chains(6);
	// some actions
	list.print();

	string expected = "6 5 4 3 2 1";
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

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(6);
	list.reverse_chains(3);
	// some actions
	list.print();

	string expected = "3 2 1 6 5 4";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

void test3() {
	cout << "\n\ntest3\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	list.insert_end(5);
	list.insert_end(6);
	list.insert_end(7);
	list.reverse_chains(2);
	// some actions
	list.print();

	string expected = "2 1 4 3 6 5 7";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

int main() {
	test1();
	test2();
	test3();

	cout << "\n\nNO RTE\n";		// must see it, otherwise RTE
	return 0;
}
