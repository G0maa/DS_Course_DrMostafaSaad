// Balance Factor, difference of height between left and righ children,
// if it's positive, means Left child has more hight than right chilc with (x ndoes)
// if it's negative, means right child has more hight than left chilc with (x ndoes)
// Balanced Binary Search Tree => Balance Factor of not more than 1. (-1, 0, 1)

// Tree rotation changing structure of a tree without changing the order of elements (in-order).
// Two Rotations:
// Right Rotation (clockwise) : Right node B goes down
// Left Rotation (counter-clockwise) : Left node A goes down
// *One child changes its parent*

// I'm not understanding the AVL insertion too well. maybe about %85.

#include <iostream>
#include <cassert>
#include <queue>
using namespace std;


class AVLTree {
private:
	struct BinaryNode {
		int data { };
		int height { };
		BinaryNode* left { };
		BinaryNode* right { };

		BinaryNode(int data) :
				data(data) {
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

	BinaryNode* insert_node(int target, BinaryNode* node) {
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target);
			else	// change left. update left as it might be balanced
				node->left = insert_node(target, node->left);
		} else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target);
			else
				node->right = insert_node(target, node->right);
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
	void insert_value(int target) {
		if (!root)
			root = new BinaryNode(target);
		else
			root = insert_node(target, root);

		verify();
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

	void level_order_traversal() {
		if (!root)
			return;

		cout << "******************\n";
		queue<BinaryNode*> nodes_queue;
		nodes_queue.push(root);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout << "Level " << level << ": ";
			while (sz--) {
				BinaryNode*cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << "\n";
		}
	}

    pair<bool, int> lower_bound(int target) { // O(log(n))
        pair<bool, int> ans = make_pair(false, -1);
        BinaryNode *node = root;
        while(node) {
            // Keeping track of visited nodes, because it may have the predeccessor.
            if(node->data > target && ans.second == -1) {
                ans.second = node->data;
                ans.first = true;
            }
            else if (node->data > target)
                ans.second = min(ans.second, node->data);

            // Normal binary traverse
            if(node->data > target) 
                node = node->left;
            else if(node->data < target)
                node = node->right;
            else
                return ans = make_pair(true, target);
        }

        // If our node has a right => Predeccsseor in it.
        if(node && node->right)
            ans.second = min_node(node->right)->data;
        return ans;
    }

	pair<bool, int> upper_bound(int target) { // O(log(n))
        pair<bool, int> ans = make_pair(false, -1);
        BinaryNode *node = root;
        while(node) {
            // Keeping track of visited nodes, because it may have the predeccessor.
            if(node->data > target && ans.second == -1) {
                ans.second = node->data;
                ans.first = true;
            }
            else if (node->data > target)
                ans.second = min(ans.second, node->data);

            // Normal binary traverse
            if(node->data > target) 
                node = node->left;
            else if(node->data < target)
                node = node->right;
            else
                break; // just changed this line
        }

        // If our node has a right => Predeccsseor in it.
        if(node && node->right)
            ans.second = min_node(node->right)->data;
        return ans;
    }

	int count_inversions(vector<int> &arr) {
		
	}
};



int main() {
    // test_bound();


	cout << "\nbye\n";
	return 0;
}

void test_bound() {
    AVLTree tree;
    tree.insert_value(2);
    tree.insert_value(5);
    tree.insert_value(10);
    tree.insert_value(13);
    tree.insert_value(15);
    tree.insert_value(20);
    tree.insert_value(40);
    tree.insert_value(50);
    tree.insert_value(70);

    assert(tree.lower_bound(70).second == 70);
    assert(tree.lower_bound(50).second == 50);
    assert(tree.lower_bound(1).second == 2);
    assert(tree.lower_bound(4).second == 5);
    assert(tree.lower_bound(10).second == 10);
    assert(tree.lower_bound(100).second == -1);

	assert(tree.upper_bound(20).second == 40);
	assert(tree.upper_bound(51).second == 70);
	assert(tree.upper_bound(13).second == 15);
	assert(tree.upper_bound(10).second == 13);
	assert(tree.upper_bound(70).second == -1);
	assert(tree.upper_bound(112).second == -1);
	cout << "Tests for lower_bound() and upper_bound() functions in AVLTree passed.\n";
}