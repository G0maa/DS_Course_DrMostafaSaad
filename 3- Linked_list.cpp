// Notice the systematic way in which the Dr. have thought of the data structure
// Think about public and private properties, add some functionalities,
// give a good time thinking about debugging functionalities
// calculate O(X) in time and space.

#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
    int data;
    Node *next = nullptr;

    Node(int data) : data(data) {}
};

class LinkedList { // I did not study OOP formally so some things are weird, marked with a +.
    private: // +
        Node* head { nullptr }; // +
        Node* tail { nullptr }; // +
        int length = 0;

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

    public: // +
    
    LinkedList () {

    }
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator = (const LinkedList &another) = delete;

    void print() {
        for(Node* cur = head; cur; cur = cur -> next)
            cout << cur -> data << ' ';
        cout << '\n';
        return;
    }

    Node* get_nth(int n) {
        int pos = 0;
        for(Node* cur = head; cur; cur = cur -> next) {
            if(pos == n) {
                return cur;
            }
            pos++;
        }
        return nullptr;
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

    int improved_search(int val) {
        int idx = 0;
        for(Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur -> next) {
            if(cur -> data = val) {
                if(!prv)
                    return idx;
                swap(prv->data, cur->data);
                return idx--;
            }
            idx++;
        }
        return -1;
    }

    void insert_end(int val) {
        Node* new_node = new Node(val);
        if(head == nullptr && tail == nullptr) { // Dr. code is much shorter :c
            head = new_node;
            // head -> data = val; // >> useless
            // head -> next = nullptr; >> useless
            tail = head; // aka head = tail = new_node;
        }
        else {
            tail -> next = new_node;
            tail = new_node;
        }
        length++;
    }

    // Debugging functions I may say:
    bool verify() {
        bool flag = 0, flag2 = 0;
        if(length == 0 && head == nullptr && tail == nullptr)
            flag = 1;

        else if(length == 1 && head == tail)
            flag = 1;

        else if(length > 1 && head != tail && tail -> next == nullptr) // forgot last part
            flag = 1;

        Node *test = get_nth(length - 1); // This is kidna different from how the dr. implemented it, his way may be better.
        if(test != nullptr && tail == test && test -> next == nullptr)
            flag2 = 1;
        
        return flag && flag2;
    }

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

    string debug_to_string () {
        if(length == 0)
            return "";
        ostringstream oss;
        for(Node *cur = head; cur; cur = cur -> next) {
            oss << cur -> data;
            if(cur -> next) 
                oss << " ";
        }
        return oss.str();
    }
};

int main() {

    LinkedList test;
    test.insert_end(3);
    test.insert_end(2);
    test.insert_end(1);
    test.print();
	return 0;
}


    // old print
    // Node* temp_head = head; // Don't screw up your head :)
    // while(temp_head != nullptr) {
    //     cout << temp_head -> data << ' ';
    //     temp_head = temp_head -> next;
    // }
    // cout << '\n';

    // int index = 0;
    // Node* last_cur = nullptr; // I initialziign it to nullptr.
    // for(Node* cur = head; cur; cur = cur -> next) {
    //     if(cur->data == val) {

    //         if(!last_cur) // I forgot this one too.
    //             return index;

    //         int temp = last_cur -> data;
    //         last_cur -> data = cur -> data;
    //         cur -> data = temp;
    //         return index - 1;
    //     }
    //     last_cur = cur;
    //     index++;
    // }