#include <iostream>
#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_set>
using namespace std;

class LinkedList {
private:
    struct Node {
    int data;
    Node *next = nullptr;

    Node(int data) : data(data) {}
    };
    Node* head { };
    Node* tail { };
    int length = 0;

public: 
    LinkedList () { }
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator = (const LinkedList &another) = delete;

    void print() {
        for(Node* cur = head; cur; cur = cur -> next)
            cout << cur -> data << ' ';
        cout << '\n';
        return;
    }

    void insert_end(int val) {
        Node* new_node = new Node(val);
        if(head == nullptr && tail == nullptr) {
            head = new_node;
            tail = head;
        }
        else {
            tail -> next = new_node;
            tail = new_node;
        }
        length++;
    }

    void create_cycle() {
        for(int i = 0; i < 4; i++)
            insert_end(i);
        Node* now = tail;
        for(int i = 0; i < 1; i++)
            insert_end(14 + i);
        tail->next = now;
    }

    // O(n)
    // I feel like there's something wrong about this solution.
    void remove_cycle() {
        unordered_set<int> list;

        // This is like an infinite loop because there's a cycle (e.e)
        // Node* last_cur = head;
        for(Node* cur = head; cur->next; cur = cur->next) {
            if(list.count(cur->next->data) == 1) {
                // last_cur->next = nullptr;
                cur->next = nullptr;
                break;
            }
            // last_cur = cur;
            list.insert(cur->data);
        }
    }
};

int main() {

    LinkedList lst;
    lst.create_cycle();
    lst.remove_cycle();
    lst.print();
	return 0;
}