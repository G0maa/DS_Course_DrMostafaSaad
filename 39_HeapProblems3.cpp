// Ez problems -> Ez.
// Medium-Hard -> 10x harder.
// tried to solve first time with 2x time ez problems, didn't work.
// then I just gave-up and gave the medium-hard problems as much time as they needed,
// solved most of them 4/6, but solutions are... meh.
// got 2/2 in the next one.
// got 2/4 in the last.
// so-> 8/12 mhm for the given time I'd say -> meh+ or OK-.
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
using namespace std;

class BinaryTree {
private:
	int data { };
	BinaryTree* left { };
	BinaryTree* right { };

public:
	BinaryTree(int data) :
			data(data) {
	}

	~BinaryTree() {
		
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

	void level_print() {
		queue<BinaryTree*> q;
		BinaryTree *cur = this;
		q.push(cur);

		while(!q.empty()) {
			cur = q.front(); q.pop();
			cout << cur->data << ' ';
			if(cur->left)
				q.push(cur->left);
			if(cur->right)
				q.push(cur->right);
		}
	}

	void level_order_traversal() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout<<"Level "<<level<<": ";
			while(sz--) {
				BinaryTree*cur = nodes_queue.front();
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
	// See solution for this, this is wrong answer, should have used priorty queue #here
	void level_order_traversal_sorted() {
		queue<BinaryTree*> nodes_queue; // #here, I understood it incorrectly.
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

            cout << "Level "<< level << ": ";
            priority_queue<int> mx_heap;
			while(sz--) {
				BinaryTree*cur = nodes_queue.front();
				nodes_queue.pop();

				mx_heap.push(cur->data);
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
            while(!mx_heap.empty()) {
                cout << mx_heap.top() << " ";
                mx_heap.pop();
            }
                
			cout << "\n";
		}
	}
};

void test() {
	BinaryTree tree(1);

	tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
	tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
	tree.add( { 2, 5, 9 }, { 'L', 'R', 'R' });
	tree.add( { 3, 6, 15 }, { 'R', 'R', 'L' });

	tree.add( { 2, 5, 13 }, { 'L', 'R', 'L' });
	tree.add( { 3, 6, 12 }, { 'R', 'R', 'R' });
	tree.add( { 3, 14, 15 }, { 'R', 'L', 'L' });
	tree.add( { 3, 14, 16 }, { 'R', 'L', 'R' });

	tree.level_order_traversal();
    cout << "\n";
	tree.level_order_traversal_sorted();
}

int main() {
	test();


	return 0;

}