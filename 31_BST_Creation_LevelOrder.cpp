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

	deque<int> level_order_traversal() {
		queue<BinarySearchTree*> nodes_queue;
		nodes_queue.push(this);
		deque<int> level_order;

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			while(sz--) {
				BinarySearchTree*cur = nodes_queue.front();
				nodes_queue.pop();

				level_order.push_back(cur->data);
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
		}
		return level_order;
	}

	void build_preorder(deque<int> &preorder_queue) {
		preorder_queue.push_back(data);

		if (left)
			left->build_preorder(preorder_queue);

		if (right)
			right->build_preorder(preorder_queue);
	}

	// BinarySearchTree(deque<int> &preorder, int min = 0, int max = 1001) {
    //     this->data = preorder.front();
    //     preorder.pop_front();
        
    //     int front = preorder.front();
    //     if(!preorder.empty() && front < this->data && front > min && front < max) {
    //         left = new BinarySearchTree(preorder, min, data);
    //     }
    //     front = preorder.front();
    //     if(!preorder.empty() && front > this->data && front > min && front < max) {
    //         right = new BinarySearchTree(preorder, data, max);
    //     }
    // }

	BinarySearchTree(deque<int> level_order) {
		this->data = level_order.front();
        level_order.pop_front();
        // Very ugly and inefficeint.
        queue<pair<BinarySearchTree*, pair<int, int>>> q;
        int min = 0;
        int max = 1001;
        pair<BinarySearchTree*, pair<int, int>> cur = make_pair(this, make_pair(min, max));
        int cur_node = level_order.front();
        q.push(cur);
        
        while(!q.empty()) {
            cur = q.front(); q.pop();
            min = cur.second.first;
            max = cur.second.second;
            if(cur_node > min && cur_node < max) {
                cur.first->left = new BinarySearchTree(cur_node);
                level_order.pop_front();
                cur_node = level_order.front();
                q.push(make_pair(cur.first->left, make_pair(min, cur.first->data)));
            }

            if(cur_node > min && cur_node < max) {
                cur.first->right = new BinarySearchTree(cur_node);
                level_order.pop_front();
                cur_node = level_order.front();
                q.push(make_pair(cur.first->right, make_pair(cur.first->data, max)));
            }
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

	tree->insert(14);
	tree->insert(16);
	tree->insert(36);
	tree->insert(58);
	// preorder: 50 20 15 14 16 45 35 36 60 58 70 73
	return tree;
}

BinarySearchTree* GetTree5() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	tree->insert(20);
	tree->insert(60);
	tree->insert(15);
	tree->insert(45);
	tree->insert(55);
	tree->insert(70);
	tree->insert(59);
	return tree;
}

BinarySearchTree* GetTree6() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	tree->insert(20);
	tree->insert(60);
	tree->insert(15);
	tree->insert(16);
	return tree;
}

void bst_from_inorder() {
	BinarySearchTree* tree = GetTree5();

	deque<int> queue1 = tree->level_order_traversal();

	BinarySearchTree tree2(queue1);

	deque<int> queue2 = tree2.level_order_traversal();

	assert(queue1 == queue2);

	for (int i = 0; i < queue2.size(); ++i) {
		cout<<queue2[i]<<" ";
	}
}

int main() {
	bst_from_inorder();

	cout << "bye\n";

	return 0;
}
