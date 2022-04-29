#include <iostream>
#include <cassert>
#include <queue>
using namespace std;

// Each binary node is a linkedlist or whatever data structure that allows insertion & deletion in O(1).
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
    
    LinkedList () {

    }
    // LinkedList(const LinkedList&) = delete;
    // LinkedList &operator = (const LinkedList &another) = delete;

    void insert(int val) { // inserts at the end
        Node* new_node = new Node(val);
        if(head == nullptr && tail == nullptr)
            head = tail = new_node;
        else {
            tail -> next = new_node;
            tail = new_node;
        }
        length++;
    }

	int remove() { // returns the needed element, removes it, and updates length.
		if(!head)
			return -1;

        int num = head->data;
		Node* delete_this = head;
		head = head -> next;
		length--;
		delete delete_this;

		if(!head)
			tail = nullptr;
        return num;
	}

	bool isEmbty() {
		return head == nullptr;
	}
};

class AVLTree {
private:
	struct BinaryNode {
		int data { };
        int height { };
        LinkedList *values = { };
		BinaryNode* left { };
		BinaryNode* right { };


        // Priority, ID
		BinaryNode(int data, int id) :
				data(data) {
            if(!values)
                values = new LinkedList();
            values->insert(id);
		}

		int ch_height(BinaryNode* node) {	// child height
			if (!node)
				return -1;			// -1 for null
			return node->height;	// 0 for leaf
		}
		int update_height() {	// call in end of insert function
			return height = 1 + max(ch_height(left), ch_height(right));
		}
		int balance_factor() {
			return ch_height(left) - ch_height(right);
		}
	};

	BinaryNode *root { };

	///////////////////////////
	bool search(int target, BinaryNode* node) {
		if(!node)
			return false;

		if (target == node->data)
			return true;

		if (target < node->data)
			return search(target, node->left);

		return search(target, node->right);
	}

	BinaryNode* right_rotation(BinaryNode* Q) {
		// cout << "right_rotation " << Q->data << "\n";
		BinaryNode* P = Q->left;
		Q->left = P->right;
		P->right = Q;
		Q->update_height();
		P->update_height();
		return P;
	}

	BinaryNode* left_rotation(BinaryNode* P) {
		// cout << "left_rotation " << P->data << "\n";
		BinaryNode* Q = P->right;
		P->right = Q->left;
		Q->left = P;
		P->update_height();
		Q->update_height();
		return Q;
	}

	BinaryNode* balance(BinaryNode* node) {
		if (node->balance_factor() == 2) { 			// Left
			if (node->left->balance_factor() == -1)	// Left Right?
				node->left = left_rotation(node->left);	// To Left Left

			node = right_rotation(node);	// Balance Left Left
		} else if (node->balance_factor() == -2) {
			if (node->right->balance_factor() == 1)
				node->right = right_rotation(node->right);

			node = left_rotation(node);
		}
		return node;
	}

	BinaryNode* insert_node(int target, int id, BinaryNode* node) {
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target, id);
			else	// change left. update left as it might be balanced
				node->left = insert_node(target, id, node->left);
		} else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target, id);
			else
				node->right = insert_node(target, id, node->right);
		}
        else  // if target(priority) already exists <<<<
            node->values->insert(id);
            
        
		node->update_height();
		return balance(node);
	}

    BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* delete_node(int target, BinaryNode* node) {
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else {
			BinaryNode* tmp = node;

			if (!node->left && !node->right)	// case 1: no child
				node = nullptr;
			else if (!node->right) 	// case 2: has left only
				node = node->left;		// connect with child
			else if (!node->left)	// case 2: has right only
				node = node->right;
			else {	// 2 children: Use successor
				BinaryNode* mn = min_node(node->right);
				node->data = mn->data; // copy & go delete
                node->values = mn->values;
				node->right = delete_node(node->data, node->right);
				tmp = nullptr;	// Don't delete me. Successor will be deleted
			}
			if (tmp)
				delete tmp;
		}
		if (node) {
			node->update_height();
			node = balance(node);
		}
		return node;
	}

    BinaryNode* dequeue_search(BinaryNode *&before_delete) {
        BinaryNode* cur = root;
		while (cur && cur->right) {
            before_delete = cur;
            cur = cur->right;
        }
            
		return cur;
	}

    int dequeue_node() {
        int ans = -1;
        BinaryNode* before_delete = nullptr;
        BinaryNode* delete_this = dequeue_search(before_delete);
        if(!(delete_this->values->isEmbty()))
            ans = delete_this->values->remove();
        
        if(delete_this->values->isEmbty()) {
            if(!before_delete)
                root = delete_node(delete_this->data, delete_this); // nullptr?
            else if(before_delete->data > delete_this->data)
                before_delete->left = delete_node(delete_this->data, delete_this);
            else
                before_delete->right = delete_node(delete_this->data, delete_this);
        }
        return ans; //...
    }

	bool is_bst(BinaryNode* node) {
		bool left_bst = !node->left || node->data > node->left->data && is_bst(node->left);

		if (!left_bst)
			return false;

		bool right_bst = !node->right || node->data < node->right->data && is_bst(node->right);
		return right_bst;
	}

	void verify() {
		assert(abs(root->balance_factor()) <= 1);
		assert(is_bst(root));
	}

	void print_inorder(BinaryNode* node) {
		if(!node)
			return;

		print_inorder(node->left);
		cout << node->data << " ";
		print_inorder(node->right);
	}


public:
	void enqueue(int id, int priority) {
		if (!root)
			root = new BinaryNode(priority, id);
		else
			root = insert_node(priority, id, root);

		verify();
	}

    int dequeue() {
        return dequeue_node();
    }

	void delete_value(int target) {
		if (root) {
			root = delete_node(target, root);
			verify();
		}
	}

	bool search(int target) {
		return search(target, root);
	}

	void print_inorder() {
		print_inorder(root);
	}

    bool isempty() {
        return root == nullptr;
    }
};



int main() {
	AVLTree tasks;

	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);
	tasks.enqueue(7761, 7);

	cout << tasks.dequeue() << "\n";	// 7761
	cout << tasks.dequeue() << "\n";	// 3161

	tasks.enqueue(1535, 1);
	tasks.enqueue(2815, 2);
	tasks.enqueue(3845, 3);
	tasks.enqueue(3145, 3);

	// 3145 3845 3111 2815 2211 1535 1131
    // not the same order, but same priority... I guess dr used some other ds.
    // mhm... I might have overthought it and created stable-srot by mistake.
    // you stopped at the whatever shitty sequennce you couldn't get.
	while (!tasks.isempty())
		cout << tasks.dequeue() << " "<<flush;

	cout<<"\n\nbye";
	return 0;
}