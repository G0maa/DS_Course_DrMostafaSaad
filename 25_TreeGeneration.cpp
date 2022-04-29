#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

class BinaryTree {
private:
	int data { };
	BinaryTree* left { };
	BinaryTree* right { };

public:
    BinaryTree(int data) : data(data) {

	}
    // passing by refrence made it overcome some bugs -> like having a root that was called before.
	BinaryTree(deque<int> &preorder, deque<int> &inorder) {
		// I guess dr code is cleaner (and less memory complexity@),
		// but generally same idea.
        this->data = preorder.front();
        preorder.pop_front();
        deque<int> first_half; // @
        deque<int> second_half; // @
        while(inorder.front() != data) {
            first_half.push_back(inorder.front());
            inorder.pop_front();
        }
        inorder.pop_front(); // data
        if(first_half.size() > 0)
            left = new BinaryTree(preorder, first_half);

        while(!inorder.empty()) {
            second_half.push_back(inorder.front());
            inorder.pop_front();
        }
        if(second_half.size() > 0)
            right = new BinaryTree(preorder, second_half);
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

	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}

    void print_preorder() {
        cout << data << " ";

		if (left)
			left->print_preorder();
		if (right)
			right->print_preorder();
	}
};

int main() {
    BinaryTree tree0(1);
	// tree0.add({2, 5, 10}, {'L', 'R', 'L'});
	// tree0.add({3, 6}, {'R', 'L'});
	// tree0.add({3, 7, 15}, {'R', 'R', 'R'});

	tree0.add({2, 5, 10}, {'L', 'R', 'L'});
	tree0.add({3, 6}, {'R', 'L'});
	tree0.add({3, 7, 15}, {'R', 'R', 'R'});
    cout << "\nTree: \n";
    tree0.print_inorder(); 
    cout << '\n';
    tree0.print_preorder();

    // in-order:  2 10 5 1 6 3 7 15  (left to right)
    // pre-order: 1 2 5 10 3 6 7 15 (roots)
    // deque<int> inorder {2, 10, 5, 1, 6, 3, 7, 15};
    // deque<int> preorder {1, 2, 5, 10, 3, 6, 7, 15};
	deque<int> inorder {15, 20, 35, 45, 50, 60, 70, 73};
    deque<int> preorder {50, 20, 15, 45, 35, 60, 70, 73};
    BinaryTree tree(preorder, inorder);
    cout << "\nMy Tree: \n";
    tree.print_inorder(); 
    cout << '\n';
    tree.print_preorder();
	cout << "\nbye\n";
	return 0;
}
