// Ez problems, I will say I got them all but in an inefficicent way.
// for lca:
//		- he recurses as long as x and y are in the same direction (both being less than this or bigger than this).
// for kth smallest
//		- similar to left boundry of a tree I think.

#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
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

public:

	// making things easier on myself.
	BinarySearchTree(deque<int> &preorder);
	BinarySearchTree(deque<int> &preorder, deque<int> &inorder);

	BinarySearchTree(int data) :
			data(data) {
	}

	void print_inorder() {
		if (left) {
			left->print_inorder();
		}
			
		cout << data << " ";
		if (right) {
			right->print_inorder();
		}
			
	}

	void give_inorder(vector<int> &inorder) {
		if (left)
			left->give_inorder(inorder);
		inorder.push_back(data);
		if (right)
			right->give_inorder(inorder);
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
	////////////////////////////////////////////

	void insert(int target) {
		if (target < data) {
			if (!left)
				left = new BinarySearchTree(target);
			else
				left->insert(target);
		} else if(target > data){
			if (!right)
				right = new BinarySearchTree(target);
			else
				right->insert(target);
		} // else: exists already
	}

	bool search(int target) {	// tail recursion
		if (target == data)
			return true;

		if (target < data)
			return left && left->search(target);

		return right && right->search(target);
	}

	bool give_search(int target, vector<int> &search_path) {	// tail recursion
		search_path.push_back(data);
		if (target == data)
			return true;

		if (target < data)
			return left && left->give_search(target, search_path);

		return right && right->give_search(target, search_path);
	}

	int min_value() {
		BinarySearchTree* cur = this;
		while (cur && cur->left)
			cur = cur->left;
		return cur->data;
	}

	bool search_iterative(int target);
	bool is_bst1();
	bool is_bst2();
	int kth_smallest(int &k);
	int lca(int first, int second);
	bool ancestors_search(int target, int &ancestor);
	void ancestors_search_interface(deque<int> &queries);
	// bool is_degen_tree(deque<int> &preorder);
};

void search_it();
void is_bst_test();
BinarySearchTree* build_balanced_bst_tree(vector<int> &values);
void balance_the_bst();
void lca_test();
void ancestors_search_test();
void is_degen_tree_test();
bool is_degen_tree(deque<int> &preorder);
void bst_form_prorder_v1();
// #main
int main() {

	BinarySearchTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);

	// Problem 1:
	// search_it();
	// Problem 2:
	// is_bst_test();
	// Problem 3:
	// balance_the_bst();
	// Problem 4:
	// no test function for this one.
	// problem 5:
	// lca_test();
	// Problem 2: #2 Queries of ancestors.
	// deque<int> v { 15, 20, 35, 45, 50, 60, 70, 73, 100 };
	// tree.ancestors_search_interface(v);
	// Problem 3:#2 Is Degen tree
	// is_degen_tree_test();
	// Problem 1#3 : BST from preorder v1
	// bst_form_prorder_v1();

	tree.print_inorder();
	
	cout << "\nbye\n";
	return 0;
}

// separate what from how, implementation from details.
// don't ask the class for information, ask the class to do the information for you.


// Problem 1:
void search_it(){
	BinarySearchTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);

	assert(tree.search_iterative(50) == 1);
	assert(tree.search_iterative(51) == 0);
	assert(tree.search_iterative(-5) == 0);
	assert(tree.search_iterative(19) == 0);
	assert(tree.search_iterative(20) == 1);
	assert(tree.search_iterative(60) == 1);
	assert(tree.search_iterative(15) == 1);
	cout << "\nsearch_it() test works!\n";
}

bool BinarySearchTree::search_iterative(int target) {
	BinarySearchTree *cur = this;
	while(cur) {
		if(cur->data == target)
			return true;
		else if(cur->left && target < cur->data)
			cur = cur->left;
		else if(cur->right && target > cur->data)
			cur = cur->right;
		else
			return false;
	}
	return false;
}

// Problem 2:
void is_bst_test(){
	BinarySearchTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);
	assert(tree.is_bst1() == 1);
	cout << "\nis_bst_test() test function works!\n";
}

// idea -> check if preorder is sorted and no repitions.
bool BinarySearchTree::is_bst1(){
	vector<int> inorder;
	give_inorder(inorder);
	for(int i = 0; i < (int) inorder.size() - 1; i++)
		if(inorder[i + 1] <= inorder[i])
			return false;

	return true;
}

// idea -> recursievly visit each node to check if BST
// 		   which is not really fundmentally different from is_bst1()
//		   so I am skipping it :U
//		   nvm... it is the way that the dr did... well...
bool BinarySearchTree::is_bst2(){
	return false;
}

// Problem 3:
void balance_the_bst(){
	vector<int> values{1, 2, 3, 10, 15, 20, 23, 24, 29, 30};
	BinarySearchTree *tree = build_balanced_bst_tree(values);
	// tree->print_inorder();
	string test = tree->parenthesize();
	cout << test;
}

// I don't like this code.
BinarySearchTree* build_balanced_bst_tree(vector<int> &values) {
	int sz = (int) values.size();
	int mid0 = (sz - 1) / 2, mid1;
	bool vis[sz] = {0};
	BinarySearchTree *tree = new BinarySearchTree(values[mid0]);
	vis[mid0] = 1;

	while(mid0 > 2) {
		mid1 = (sz + mid0) / 2;
		mid0 /= 2;
		vis[mid0] = 1;
		vis[mid1] = 1;
		tree->insert(values[mid0]);
		tree->insert(values[mid1]);
	}
	for(int i = 0; i < sz; i++)
		if(vis[i] == 0)
			tree->insert(values[i]);
	
	return tree;
}

// Problem 4:
// hmmmm...
int BinarySearchTree::kth_smallest(int &k) {
	vector<int> inorder;
	give_inorder(inorder);
	return inorder[k - 1];
}

// Problem 5:
// I suppose there's a better recursive solution.
void lca_test() {
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

	cout << tree->lca(35, 60) << "\n";
	cout << tree->lca(14, 16) << "\n";
	cout << tree->lca(70, 73) << "\n";
}

int BinarySearchTree::lca(int first, int second) {
	vector<int> search_path_first;
	vector<int> search_path_second;
	give_search(first, search_path_first);
	give_search(second, search_path_second);

	int max_sz = max((int) search_path_second.size(), (int) search_path_first.size());
	int ans = search_path_second[0];
	for(int i = 0; i < max_sz; i++) {
		if(search_path_first[i] != search_path_second[i]) {
			ans = search_path_second[i - 1];
			break;
		}
	}
	return ans;
}

// Problem 2#2: Very small changes.
// wrong answer, he wanted it in a more efficient way.
// idea of dr solution: 
// You search for quries.front() normally,
// you insert into traversal vector, 
// when (if condition) queries.front() == traversal.back()
// you found the successor put it in the answer and search for next in queries.
void ancestors_search_test(){
	BinarySearchTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);

	deque<int> v { 15, 20, 35, 45, 50, 60, 70, 73, 100 };

	for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
		int ancestor = -1;
		bool flag = tree.ancestors_search(v[i], ancestor);

		if (flag && ancestor != -1) // extra condition here
			cout << ancestor << "\n";
		else
			cout << "NA\n";

	}
	cout << "bye\n";
}

// Problem 2#2: Very small changes.
void  BinarySearchTree::ancestors_search_interface(deque<int> &queries) {
	deque<int> ans;
	while(!queries.empty()) {
		int ancestor = -1;
		bool flag = this->ancestors_search(queries.front(), ancestor);
		// cout << queries.front() << ' ';
		queries.pop_front();
		if (flag && ancestor != -1) // extra condition here
			ans.push_back(ancestor);
		else
			ans.push_back(-1);
	}
	// just for printing you can return ans instead.
	while(!ans.empty()) {
		cout << ans.front() << ' ';
		ans.pop_front();
	}
}

bool BinarySearchTree::ancestors_search(int target, int &ancestor) {
	if (target == data) {
		if(right)
			ancestor = right->min_value();
		if(ancestor <= target)
			ancestor = -1;
		return true;
	}
		

	if (target < data) {
		ancestor = this->data;
		return left && left->ancestors_search(target, ancestor);
	}
	
	return right && right->ancestors_search(target, ancestor);
}

// Problem 3:#3 is degen tree (switched to deque for easier manipulation)
// mhm... not clean.. at all.. but hopefully correct?
// solution has similar idea but.... much like MUCH more cleaner :c
void is_degen_tree_test(){
	deque<int> a;

	a = {25, 8, 11, 13, 12};
	assert(is_degen_tree(a));

	a = {100, 70, 101};
	assert(!is_degen_tree(a));

	a = {100, 70, 60, 75};
	assert(!is_degen_tree(a));

	a = {100, 70, 60, 65};
	assert(is_degen_tree(a));

	a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	assert(is_degen_tree(a));

	a = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	assert(is_degen_tree(a));

	a = {500, 400, 300, 200 , 250 , 275, 260};
	assert(is_degen_tree(a));

	a = {500, 400, 300, 200 , 250 , 275, 260, 280};
	assert(!is_degen_tree(a));
}

bool is_degen_tree(deque<int> &preorder) {
	int parent = preorder.front(); preorder.pop_front();
	int child = preorder.front(); preorder.pop_front();
	bool is_ascending = false;
	bool swap = false;
	if(child > parent)
		is_ascending = true;
	
	// limits activate when there exists swaps from descinding to ascending or vice versa.
	int ascending_limit = 1001;
	int descinding_limit = -1;

	while(!preorder.empty()) {
		int front = preorder.front();
		if(is_ascending) {
			if(child < front) {
				if(front > ascending_limit)
					return false;
				parent = child;
				child = front;
				preorder.pop_front();
			}
			else
				swap = true;
		}
		else {
			if(child > front) {
				if(front < descinding_limit)
					return false;
				parent = child;
				child = front;
				preorder.pop_front();
			}
			else
				swap = true;
		}

		if(swap) {
			if(is_ascending) {
				is_ascending = false;
				descinding_limit = parent;
				if(front < descinding_limit)
					return false;
				parent = child;
				child = front;
				preorder.pop_front();
			}
			else {
				is_ascending = true;
				ascending_limit = parent;
				if(front > ascending_limit)
					return false;
				parent = child;
				child = front;
				preorder.pop_front();
			}
		}
	}
	return true;
}

// Problem 1#3:
// same old problem + soriing to get in-order
// probably not the inteded way but oh well :U
// hmmm after seeing the solution... I think mine has somewhat the same basis
// but first_half & second_half creation just made it slower.
void bst_form_prorder_v1(){
	deque<int> test{50, 20, 15, 45, 35, 60, 70, 73};
	// BinarySearchTree *tree = new BinarySearchTree(test);
	BinarySearchTree tree(test);
	tree.print_inorder();
}
// I just switched BST to BT I guess, not using the usefulness of BST
// But I did what's required in a diffeerent way? -> O(n^2)
BinarySearchTree::BinarySearchTree(deque<int> &preorder) {
	int i = 0;
	int sz = preorder.size();
	deque<int> inorder;
	for(int i = 0; i < sz; i++)
		inorder.push_back(preorder[i]);
	sort(inorder.begin(), inorder.end());
	// mhm... looks... risky?
	*this = BinarySearchTree(preorder, inorder);	
}

BinarySearchTree::BinarySearchTree(deque<int> &preorder, deque<int> &inorder) {
	this->data = preorder.front();
	preorder.pop_front();
	deque<int> first_half;
	deque<int> second_half;
	while(inorder.front() != data) {
		first_half.push_back(inorder.front());
		inorder.pop_front();
	}
	inorder.pop_front(); // data
	if(first_half.size() > 0)
		left = new BinarySearchTree(preorder, first_half);

	while(!inorder.empty()) {
		second_half.push_back(inorder.front());
		inorder.pop_front();
	}
	if(second_half.size() > 0)
		right = new BinarySearchTree(preorder, second_half);
}