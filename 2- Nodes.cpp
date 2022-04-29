#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int data;
    Node *next = nullptr;

    Node(int data) : data(data) {}
};

void print1(Node* head) {
    while(head != nullptr) {
        cout << head -> data << ' ';
        head = head -> next;
    }
    cout << '\n';
    return;
}

void print_forloop(Node* head) {
    
    for(int i = 0; head != nullptr; i++) {
        cout << head -> data << ' ';
        head = head -> next;
    }
    cout << '\n';
    return;
}

void print_rec(Node* head) {
    if(head == nullptr) // forgot '\n' here.
        return;
    cout << head -> data << ' '; // print in reverse? switch this line with the line under it.
    print_rec(head -> next);
    return;
}

Node* find_node(Node* head, int value) {
    while(head != nullptr) {
        if(head -> data == value)
            return head;
        head = head -> next;
    }
    return nullptr;
}

int main() {

    Node* node1 = new Node(14);
	Node* node2 = new Node(2);
    Node* node3 = new Node(4);
    Node* node4 = new Node(1);
    node1 -> next = node2;
    node2 -> next = node3;
    node3 -> next = node4;
    node4 -> next = nullptr;
    // print_forloop(node1);
    cout << find_node(node1, 2);
	return 0;
}
