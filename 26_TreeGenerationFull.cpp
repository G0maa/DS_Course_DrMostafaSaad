// this is probably the cleanest code I have ever written considering the time put into it
// maybe the reason is that yesterday I had no DS-course?
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

// needed data structures:
deque<int> preorder;
deque<bool> is_leaf;

class BinaryTree {
private:
	int data { };
	BinaryTree* left { };
	BinaryTree* right { };

public:
    BinaryTree(int data) : data(data) {

	}
    // passing by refrence made it overcome some bugs -> like having a root that was called before.
	BinaryTree(deque<int> &preorder, deque<bool> &is_leaf) {
		// again I think same idea & complexity but spaghitti code on my side.		
		this->data = preorder.front();
		preorder.pop_front();

		// hmmm... is is_leaf ordered for our sake?
		bool yes_leaf = is_leaf.front();
		is_leaf.pop_front();
		if(preorder.size() > 0 && !yes_leaf)
			left = new BinaryTree(preorder, is_leaf);

		if(preorder.size() > 0 && !yes_leaf)
			right = new BinaryTree(preorder, is_leaf);
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		BinaryTree* current = this;
		// iterate on the path, create all necessary nodes
		for (int i = 0; i < (int) values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new BinaryTree(values[i]);
				else
					assert(current->left->data == values[i]);
				current = current->left;
			} else {
				if (!current->right)
					current->right = new BinaryTree(values[i]);
				else
					assert(current->right->data == values[i]);
				current = current->right;
			}
		}
	}

    void print_preorder() { // and leaves.
		cout << data << ' ';
        preorder.push_back(data);

		// well... will that work?
		if(left && right)
			is_leaf.push_back(0);
		else
			is_leaf.push_back(1);

		if (left)
			left->print_preorder();
		if (right)
			right->print_preorder();
	}

	// just for testing.
	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << ' ';
		if (right)
			right->print_inorder();
	}	
};

int main() {
	// test 0
	BinaryTree tree0(1);

	// test 1
	// tree0.add({2, 4}, {'L', 'L'});
	// tree0.add({2, 5}, {'L', 'R'});
	// tree0.add({3, 6}, {'R', 'L'});
	// tree0.add({3, 7}, {'R', 'R'});

	// test 2
	// tree0.add({2, 4}, {'L', 'L'});
	// tree0.add({2, 5}, {'L', 'R'});
	// tree0.add({3}, {'R'});

	// test 3 (opposite of test 2) -> notice symmetry
	// tree0.add({2, 4}, {'R', 'R'});
	// tree0.add({2, 5}, {'R', 'L'});
	// tree0.add({3}, {'L'});

	// test 4 (degenerate) -> a rather small one.
	// tree0.add({2}, {'L'});
	// tree0.add({3, 4}, {'R', 'L'});
	// tree0.add({3, 5, 6}, {'R', 'R', 'L'});
	// tree0.add({3, 5, 7}, {'R', 'R', 'R'});

	tree0.print_preorder();
	cout << '\n';
	tree0.print_inorder();
	// tree0.give_some_leaves();
	// while(!is_leaf.empty()) {
	// 	cout << is_leaf.front() << ' ';
	// 	is_leaf.pop_front();
	// }
	
	BinaryTree tree(preorder, is_leaf);
	cout << '\n';
	tree.print_preorder();
	cout << '\n';
	tree.print_inorder();
	// tree.give_some_leaves();
	// while(!is_leaf.empty()) {
	// 	cout << is_leaf.front() << ' ';
	// 	is_leaf.pop_front();
	// }
	cout << "\nbye\n";
	return 0;
}
