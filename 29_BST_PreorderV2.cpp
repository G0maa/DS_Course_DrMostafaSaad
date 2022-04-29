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

public:

	BinarySearchTree(int data, BinarySearchTree* left = nullptr, BinarySearchTree* right = nullptr) :
			data(data), left(left), right(right) {
	}

	void print_inorder() {
		if (left)
			left->print_inorder();

		cout<<data<<" ";
		if (right)
			right->print_inorder();
	}

	void insert(int target) {
		if (target < data) {
			if (!left) {
				left = new BinarySearchTree(target);
			} else
				left->insert(target);
		} else if (target > data) {
			if (!right)
				right = new BinarySearchTree(target);
			else
				right->insert(target);
		} // else: exists already
	}

	////////////////////////////////////////////

	void build_preorder(deque<int> &preorder_queue) {
		preorder_queue.push_back(data);

		if (left)
			left->build_preorder(preorder_queue);

		if (right)
			right->build_preorder(preorder_queue);
	}

	BinarySearchTree(deque<int> &preorder, vector<int> &next_greater, int start = 0, int end = -1) {
		if (end == -1) 
            end = (int) preorder.size() - 1;
			
		// next preorder is the current root
		data = preorder[start];

		int split = next_greater[start];

        if (split == end+1 || preorder[split] > data) {
            if (start+1 <= split-1)	// there is a left tree
                left = new BinarySearchTree(preorder, next_greater, start+1, split - 1);
            if (split <= end)
                right = new BinarySearchTree(preorder, next_greater, split, end);
        }
	}

};


BinarySearchTree* GetTree1() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	return tree;
}

BinarySearchTree* GetTree2() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	tree->insert(20);
	tree->insert(10);
	tree->insert(5);
	return tree;
}

BinarySearchTree* GetTree3() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	tree->insert(60);
	return tree;
}

BinarySearchTree* GetTree4() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	tree->insert(20);
	tree->insert(60);
	tree->insert(15);
	tree->insert(45);
	tree->insert(70);
	tree->insert(35);
	tree->insert(73);

	// preorder: 50 20 15 45 35 60 70 73
	return tree;
}

BinarySearchTree* GetTree5() {
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
	// preorder: 50 20 15 14 16 45 35 36 60 58 70 73
	return tree;
}

vector<int> next_greater_idx(deque<int> &preorder) {
    int len = preorder.size();
    vector<int> ans(len);
    for(int i = 0; i < len; i++)
        ans[i] = preorder[i];

    stack<int> pos;
    for (int i = 0; i < (int) len; ++i) {
        while (!pos.empty() && ans[i] > ans[pos.top()]) {
            ans[pos.top()] = i; pos.pop();
        }
        pos.push(i);
    }

    while (!pos.empty()) {
        ans[pos.top()] = len; 
        pos.pop();
    }
        
    return ans;
}

void bst_from_preorder() {
	BinarySearchTree* tree = GetTree5();

	deque<int> preorder_queue;

	tree->build_preorder(preorder_queue);

	if(true) {
		for (int i = 0; i < preorder_queue.size(); ++i) {
			cout<<preorder_queue[i]<<" ";
		}
		cout<<"\n";
	}

    vector<int> next_greater = next_greater_idx(preorder_queue);
    // for(int i = 0; i < (int) next_greater.size(); i++)
    //     cout << next_greater[i] << ' ';
	BinarySearchTree new_tree(preorder_queue, next_greater);
	new_tree.print_inorder();	// must be sorted
}

int main() {
	bst_from_preorder();

	cout << "bye\n";

	return 0;
}

