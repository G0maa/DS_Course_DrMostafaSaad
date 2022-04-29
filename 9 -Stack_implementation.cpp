#include <bits/stdc++.h>
using namespace std;

class Stack {
    private:
        int top { };
        int size { };
        int *arr;
    
    public:
        Stack(int size) : 
                size(size), top(-1) {
            arr = new int [size];
        }

        int peek () {
            assert(top != -1);
            return arr[top];
        }

        void push (int val) {
            assert(top + 1 != size);
            top++;
            arr[top] = val;
        }

        int pop () {
            assert(top != -1);
            int temp = arr[top];
            // arr[size - 1] = 0; ?
            top--;
            return temp;
        }
};

struct Node {
    int data { };
    Node *next { };
    
    Node(int data) : data(data) {}
};

class LinkedStack {
    private:
        Node *head { };
        int size = 0;
    
    public:
        int peek () {
            assert(head);
            return head->data;
        }

        void push (int val) {
            Node* new_node = new Node(val);
            if(!head) {
                head = new_node;
                return;
            }
            new_node->next = head;
            head = new_node;
            size++;
        }

        int pop () {
            assert(head);
            Node *tempn = head;
            int temp = tempn->data;
            head = head->next;
            delete tempn;
            size--;
            return temp;
        }
};

int main () {
    Stack stk(3);
    stk.push(3);
    stk.pop();
    stk.pop();
    cout << stk.peek();

    cout << "\n\n NO RTE \n\n";
}