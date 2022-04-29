// Balance Factor, difference of height between left and righ children,
// if it's positive, means Left child has more hight than right chilc with (x ndoes)
// if it's negative, means right child has more hight than left chilc with (x ndoes)
// Balanced Binary Search Tree => Balance Factor of not more than 1. (-1, 0, 1)

// Tree rotation changing structure of a tree without changing the order of elements (in-order).
// Two Rotations:
// Right Rotation (clockwise) : Right node B goes down
// Left Rotation (counter-clockwise) : Left node A goes down
// *One child changes its parent*


#include <iostream>
#include <cassert>
#include <queue>
using namespace std;


class AVLTree {
private:
	struct BinaryNode {
		int data { };
        int idx { }; // cjamged
		int height { };
		BinaryNode* left { };
		BinaryNode* right { };

		BinaryNode(int data, int idx) : // changed
				data(data), idx(idx) {
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
	int search(int target, int idx_target, BinaryNode* node) { // turned to iterative for ease of use... 
		int ans = 0;                          // I am assuming that the tree is used only for count_inversions()
        while(node) {
            if(node->idx < idx_target && node->data < target) // <<
                ans++;

            if(node->data > target) 
                node = node->left;
            else if(node->data < target)
                node = node->right;
            else
                break;
        }
        return ans;
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

	BinaryNode* insert_node(int target, int idx, BinaryNode* node) { // changed
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target, idx);
			else	// change left. update left as it might be balanced
				node->left = insert_node(target, idx, node->left);
		} else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target, idx);
			else
				node->right = insert_node(target, idx,node->right);
		}
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
				node->data = mn->data;	// copy & go delete
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
	void insert_value(int target, int idx) { //changed
		if (!root)
			root = new BinaryNode(target, idx);
		else
			root = insert_node(target, idx, root);

		verify();
	}

	void delete_value(int target) {
		if (root) {
			root = delete_node(target, root);
			verify();
		}
	}

	bool search(int target, int idx_target) {
		return search(target, idx_target, root);
	}

	void print_inorder() {
		print_inorder(root);
	}

    // reverse thinking, you search for the number normally in log(n), along the way
    // you check if numbers less than you have index before you, then you subtract that number from your curent index
    // so you have your answer for that number.
	// WRONG.
	int count_inversions(vector<int> &arr) {
        int ans = 0;
        int arr_len = arr.size();
		for(int i = 0; i < arr_len; i++) // O(nlogn)
            insert_value(arr[i], i);
        
        for(int i = 0; i < arr_len; i++) { // O(nlogn) 
            cout << "Searching for: " << arr[i] << " Result: " << search(arr[i], i) << '\n';
            // ans += i - search(arr[i], i);
        }
        return ans;
	}
};



int main() {
    AVLTree test;
    vector<int> arr {10, 5, 8, 2, 12, 6};
    // vector<int> arr {5, 4, 3, 2, 1};
    cout << test.count_inversions(arr) << '\n';

	cout << "\nbye\n";
	return 0;
}