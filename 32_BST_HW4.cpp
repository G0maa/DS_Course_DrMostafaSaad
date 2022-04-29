#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class BinarySearchTree {
private:
	int data { };
	BinarySearchTree* left { };
	BinarySearchTree* right { };

	BinarySearchTree* max_node() {
		BinarySearchTree* cur = this;
		while (cur && cur->right)
			cur = cur->right;
		return cur;
	}

	void special_delete(BinarySearchTree* child) {
		// Instead of deleting node and return its child
		// copy child data and remove him
		// why? as sometimes node is actually the original this
		// Deleting it is RTE
		// This is another complication we pay for our coding style
		// to use only a single class instead of class + struct like linkedlist
		data = child->data;
		left = child->left;
		right = child->right;
		delete child;
	}

	// Delete the target node in the tree and return updated tree
	// Caller use updated tree to re-link with children!
	// BinarySearchTree* delete_node(int target, BinarySearchTree* node) {
	// 	if (!node)
	// 		return nullptr;

	// 	if (target < node->data)
	// 		node->left = delete_node(target, node->left);
	// 	else if (target > node->data)
	// 		node->right = delete_node(target, node->right);
	// 	else {
	// 		if (!node->left && !node->right) {
	// 			delete node;
	// 			node = nullptr;
	// 		}
	// 		else if (!node->right) 	// case 2: has left only
	// 			node->special_delete(node->left);		// connect with child
	// 		else if (!node->left)	// case 2: has right only
	// 			node->special_delete(node->right);
	// 		else {	// 2 children: Use successor
	// 			BinarySearchTree* mx = node->left->max_node();
	// 			node->data = mx->data;	// copy & go delete
	// 			node->left = delete_node(node->data, node->left);
	// 		}
	// 	}
	// 	return node;
	// }

    // delete but no recursion... hopefully I didn't over complicate it.
    void delete_node(int target, BinarySearchTree *last = nullptr, bool is_left = false) {
        BinarySearchTree *cur  = this;
        // bool is_left = false;
		while(cur) {
            if (target < cur->data) {
                last = cur;
                cur = cur->left;
                is_left = true;
            }
            else if (target > cur->data) {
                last = cur;
                cur = cur->right;
                is_left = false;
            }
            else {
                if (!cur->left && !cur->right) {
                    delete cur;
                    cur = nullptr;
                }
                else if (!cur->right) {
                    // case 2: has left only
                    cur->special_delete(cur->left);		// connect with child
                    break;
                } 	
                else if (!cur->left) {
                    // case 2: has right only
                    cur->special_delete(cur->right);
                    break;
                }	
                else {	// 2 children: Use successor
                    BinarySearchTree* mn = cur->left->max_node();
                    cur->data = mn->data;	// copy & go delete
                    // separate function, not recursive call.
                    // last has predecessor on its left.
                    cur->left->delete_node(cur->data, cur, true);
                }

                if(is_left)
                    last->left = cur;
                else
                    last->right = cur;
            }
        }
	}

public:

	BinarySearchTree(int data) :
			data(data) {
	}

	void get_inorder(vector<int>& values) {
		if (left)
			left->get_inorder(values);
		values.push_back(data);
		if (right)
			right->get_inorder(values);
	}
	////////////////////////////////////////////

	void insert(int target) {
		if (target < data) {
			if (!left) {
				left = new BinarySearchTree(target);
			}
			else
				left->insert(target);
		} else if (target > data) {
			if (!right)
				right = new BinarySearchTree(target);
			else
				right->insert(target);
		} // else: exists already
	}

	void delete_value(int target) {
		if (target == data && !left && !right)
			return;	// can't remove root in this structure
		delete_node(target, this);
		// delete_node(target);
	}
};

BinarySearchTree* GetTree1() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	tree->insert(20);
	tree->insert(60);
	tree->insert(15);
	tree->insert(45);
	tree->insert(70);
	tree->insert(35);
	tree->insert(73);

	tree->insert(14);
	tree->insert(16);
	tree->insert(36);
	tree->insert(58);
	return tree;
}

BinarySearchTree* GetTree2() {
	BinarySearchTree* tree = new BinarySearchTree(10);
	tree->insert(5);
	return tree;
}

void test1() {
	BinarySearchTree* tree = GetTree1();

	// tree->delete_value(10);
	// tree->insert(7);
	// tree->insert(15);

    vector<int> inorder;
	tree->get_inorder(inorder);
    for (int i = 0; i < (int) inorder.size(); ++i)
        cout << inorder[i] << ' ';
}

void test2() {
	BinarySearchTree* tree = GetTree1();

	vector<int> inorder;
	tree->get_inorder(inorder);

	for (int i = 0; i < (int) inorder.size(); ++i) {
		if (inorder[i] == 50)
			continue;	// root

		vector<int> inorder_v2;
		BinarySearchTree* tree = GetTree1();
		tree->delete_value(inorder[i]);
		tree->get_inorder(inorder_v2);

		vector<int> inorder_cpy = inorder;
		inorder_cpy.erase(find(inorder_cpy.begin(), inorder_cpy.end(), inorder[i]));
		assert(inorder_cpy == inorder_v2);
	}
}

int main() {

	test2();

	cout << "bye\n";

	return 0;
}

