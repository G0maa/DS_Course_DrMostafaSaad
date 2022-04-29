#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

string toStr(int n) {
	// Convert integer to string
	ostringstream oss;
	oss << n;
	return oss.str();
}


class BinarySearchTree {
private:
	int data { };
	BinarySearchTree* left { };
	BinarySearchTree* right { };
    BinarySearchTree* parent { };

public:

	BinarySearchTree(int data, BinarySearchTree *parent) :
			data(data), parent(parent) {
	}

	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
	////////////////////////////////////////////

	void insert(int target) {
		if (target < data) {
			if (!left)
				left = new BinarySearchTree(target, this);
			else
				left->insert(target);
		} else if (target > data) {
			if (!right)
				right = new BinarySearchTree(target, this);
			else
				right->insert(target);
		} // else: exists already
	}

    // updated it for child... thinking about it again...
    // this is a major void of OO concepts lol
    // returning a refrence to an element in the DS, which can:
    // - be deleted, and I can edit it, or many possible other things.

	bool search(int target, BinarySearchTree* &child) {
		if (target == data) {
            child = this;
            return true;
        }
			
		if (target < data)
			return left && left->search(target, child);

		return right && right->search(target, child);
	}

	int min_value() {
		BinarySearchTree* cur = this;
		while (cur && cur->left)
			cur = cur->left;
		return cur->data;
	}
	
	pair<bool, int> successor(int target) {
        BinarySearchTree *child, *child_parent;
		if (!search(target, child))	// not exist
			return make_pair(false, -1);

		if (child->right)
			return make_pair(true, child->right->min_value());

		child_parent = child->parent;

		while (child_parent && child_parent->right == child)
			child = child_parent, child_parent = child_parent->parent;

		if (child_parent)
			return make_pair(true, child_parent->data);
		return make_pair(false, -1);
	}
    
    void check(){
        cout << this->parent->data;
    }

    string parenthesize() {
		string repr = "(" + toStr(data);

		if (left)
			repr += left->parenthesize();
		else
			repr += "()";	// null: no child

		if (right)
			repr += right->parenthesize();
		else
			repr += "()";	// null: no child
		repr += ")";

		return repr;
	}
};

int main() {
	BinarySearchTree tree(50, nullptr);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);

    // cout << tree.parenthesize() << '\n';
    // BinarySearchTree *child;
    // tree.search(35, child);
    // child->check();
	// tree.print_inorder();
	vector<int> v { 15, 20, 35, 45, 50, 60, 70, 73, 100 };

	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
		pair<bool, int> p = tree.successor(v[i]);

		if (p.first)
			cout << p.second << "\n";
		else
			cout << "NA\n";

	}

	cout << "bye\n";

	return 0;
}

