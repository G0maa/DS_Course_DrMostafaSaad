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


string toStr(int n) {
	// Convert integer to string
	ostringstream oss;
	oss << n;
	return oss.str();
}

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

	void print_inorder() {
		if(left)
			left->print_inorder();
		cout << data << " ";
		if(right)
			right->print_inorder();
	}

	void give_inorder(vector<int> &inorder) {
		if (left)
			left->give_inorder(inorder);
		inorder.push_back(data);
		if (right)
			right->give_inorder(inorder);
	}

	bool is_bst1(){
		vector<int> inorder;
		give_inorder(inorder);
		for(int i = 0; i < (int) inorder.size() - 1; i++)
			if(inorder[i + 1] <= inorder[i])
				return false;

		return true;
	}

	void print_preorder() {
		cout << data << " ";
		if(left)
			left->print_preorder();
		if(right)
			right->print_preorder();
	}
	void print_preorder_complete() {
		if(!this) {
			cout << 0 << ' ';
			return;
		}
		cout << data << " ";
		
		// if(left)
			left->print_preorder_complete();
		
		// if(right)
			right->print_preorder_complete();
	}
	void print_inorder_iterative() { // Yeah... not clean... at all.
		// dr has a very nice solution which depends on how he organized the code,
		// to aid him in having an "ordered" stack of pointers to print eventually.
		// well... I didn't have that :c
		stack<pair<BinaryTree*, int>> st;
		pair<BinaryTree*, int> cur = make_pair(this, 0);
		st.push(cur);

		while(!st.empty()) {
			cur = st.top();
			if(cur.second == 0) {
				if(cur.first->left) {
					cur.first = cur.first->left;
					st.push(cur);
				} else {
					cout << cur.first->data << ' ';
					st.pop();
					cur.second = 1;
					st.push(cur);
				}
			} else if(cur.second == 1) {
				if(cur.first->right) {
					cur.first = cur.first->right;
					cur.second = 0;
					st.push(cur);
				} else {
					st.pop();
					cur.second = 2;
					st.push(cur);
				}
			} else {
				st.pop();
				if(st.empty()) // one node left, its second >= 2.
					break;
				cur = st.top();
				if(cur.second == 0)
					cout << cur.first->data << ' ';
				cur.second++;
				st.pop();
				if(cur.second < 2)
					st.push(cur);
				else {
					cur = st.top();
					if(cur.second == 0) // this for root only I think
						cout << cur.first->data << ' ';
					cur.second++;
					st.pop();
					st.push(cur);
				}
			}
		}
	}

	void print_test() {
		if(!this)
			return;

		left->print_inorder();
		cout << data << " ";
		right->print_inorder();
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

	int tree_max() { // dr's code cleaner & shorter but same idea.
		if(!this)
			return 0;

		int max = -10, temp; // big small number
		if(left) {
			temp = left->tree_max(); // could have used max0 = max(max0, left->tree_max());
			if(temp > max)
				max = temp; 
			
		}
			
		if(right) {
			temp = right->tree_max();
			if(temp > max)
				max = temp;
		}
		
		if(data > max)
			max = data;
		return max;
	}

	int tree_height() { // similar to dr's code, I'd say ok.
		if(!this)
			return 0;

		int height = -1; // just to ignore the root node.
		if(left)
			height = max(height, left->tree_height()); // dr added 1+ here.

		if(right)
			height = max(height, right->tree_height());
		
		height++;
		return height;
	}
		
	int count_nodes() { // ok.
		if(!this)
			return 0;
		
		int cnt = 0;

		if(left)
			cnt += left->count_nodes();

		if(right)
			cnt += right->count_nodes();
		
		cnt++;
		return cnt;
	}

	int count_leaf() {
		if(!this)
			return 0;
		int cnt = 0;
		if(!left->count_leaf() && !right->count_leaf())
			cnt++;
		else {
			if(left)
				cnt += left->count_leaf();

			if(right)
				cnt += right->count_leaf();
		}

		return cnt;
	}

	bool is_exist(int value) { // neat? dr's recursive homework :)
		if(!this)
			return false;
		
		if(data == value)
			return true;
		
		return (left->is_exist(value) || right->is_exist(value));
	}

	bool is_perfect(int h = -1) {
		if (h == -1)	// first call
			h = tree_height();

		// All leaves must be on the same last level
		if (!left && !right)
			return h == 0;

		if (!left && right || left && !right)
			return false;	// one child!

		// perfect on level h is perfect on h-1 for children
		return left->is_perfect(h - 1) && right->is_perfect(h - 1);
	}

	// bool is_perfect(int height = -1) { // wrong solution, couldn't get it.
	// 	if(!this)					// I was close to the idea, but wasn't botherd to lose more time for it.
	// 		return false;
	// 	// correct answer:
	// 	// calculate height when h == -1
	// 	// if node has one child -> return false.
	// 	// if node is leaf -> make sure h == 0
	// 	// h - 1 in each time you go down.
	// 	if(left->is_perfect() && right->is_perfect()) // can be put in the same line but will be lenngthy.
	// 		return true;
	// 	else if(!left->is_perfect() && !right->is_perfect()) {
	// 		return true;
	// 	}
			
	// 	else
	// 		return false;

	// 	return (left->is_perfect() && right->is_perfect());
	// }

	bool is_perfect0() {
		int height = this->tree_height();
		int nodes = this->count_nodes();

		if(nodes == (pow(2, height + 1) - 1))
			return true;
		
		return false;
	}
	void clear() {
		//	couldn't solve this one, although easy.
		// thing is I kept testing if it got cleared or not.
		// but it didn't -> I tried printing them, 
		// dr just put them to nullptrs.
		// is that really clear?

		// if(left)
		// 	return left->clear();
		// if(right)
		// 	return right->clear();
		
		// if(!left && !right)
		// 	delete this;
		delete left;
	}

	void traverse_left_boundry() {
		cout << data << ' ';

		if(!left && !right)
			return;		
		else if(left)
			left->traverse_left_boundry();
		else if(right)
			right->traverse_left_boundry();
		return;
	}

	int longest_path_length() { // root node returns one, kind of inefficient I guess.
								// I'm getting the idea of dr's code, but not eniterly.
		int a = 0, b = 0, res = 0;
		if (left) {
			res = left->longest_path_length();
			a = 1 + left->tree_height();
		}
			
		if (right) {
			res = max(res, right->longest_path_length());
			b = 1 + right->tree_height();
		}

		if(a + b + 1 > res)
			res = a + b + 1;
		return res;
	}

	void level_print() { // you can add level funcationalitiy by
						// 1- pair
						// 2- save in an external variable (efficient) (BFS)
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

	// Yeah... probably not the intended way eh?
	// nvm... dr code has the same idea.
	void level_print_rec(int lvl = -1) { // O(n + ((n*n-1)/2) -> ~n^2
		if(lvl == -1) {
			lvl = this->tree_height();
			for(int i = 0; i < lvl; i++)
				level_print_rec(i);
		}
		
		if(lvl == 0) {
			cout << data << ' ';
		}
		else {
			if(left) left->level_print_rec(lvl - 1);
			if(right) right->level_print_rec(lvl - 1);
		}
	}

	// mhm kind of different idea, my answer is a bit slower.
	void level_order_traversal_spiral() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		bool rev = false; // +
		int level = 0;
		stack<BinaryTree*> st; // +
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout<<"Level "<<level<<": ";
			while(sz--) {
				BinaryTree*cur = nodes_queue.front();
				nodes_queue.pop();

				if(!rev) // +
					cout << cur->data << " ";

				if (cur->left) {
					nodes_queue.push(cur->left);
					if(!rev) { // +
						st.push(cur->left);
					}
				}
					
				if (cur->right) {
					nodes_queue.push(cur->right);
					if(!rev) { // +
						st.push(cur->right);
					}
				}
					
			}

			while(!st.empty() && rev) // +
				cout << st.top()->data << ' ', st.pop();
			rev = !rev; // +
			level++;
			cout << "\n";
		}
	}

	// dr code is cleaner... at least it came only to that : )
	bool is_complete() { // normal level-order traverse + little extra logic
		int height = this->tree_height();
		int n_nodes = 1, level = 0, sz;

		BinaryTree *cur;
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		while (!nodes_queue.empty()) {
			sz = nodes_queue.size();
			if(sz < n_nodes)
				return false;

			if(level + 1 == height) // ?
				break;
			
			while(sz--) {
				cur = nodes_queue.front();
				nodes_queue.pop();

				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}

			n_nodes *= 2;
			level++;
			cout << "\n";
		}

		sz = (int) nodes_queue.size();
		if(sz == 0)
			return true;
		for(int i = 0; i < sz; i++) {
			cur = nodes_queue.front(); nodes_queue.pop();
			if(cur->right && !cur->left)
				return false;
			if(cur->left && !cur->right && i + 1 < sz)
				return false;
			if(!cur->left && !cur->right && i + 1 < sz)
				return false;
		}
		return true;
	}

	// I wanted to edit it to allow no arguments, but I decided to leave it as is,
	// and see how the dr did it.

	bool is_symmetric(BinaryTree *first, BinaryTree *second) { // O(n) (whole tree or sum of both sub-trees)
		if(!first && !second)
			return true;
		if(!first || !second)
			return false;
		if(first->data != second->data)
			return false;

		return is_symmetric(first->right, second->left) && is_symmetric(first->left, second->right);
	}
	// couldn't solve thi one.
	// dr code explaination -> edited parantehsize() 
	// to have a flag, if flag is true then insert right then left, if flag is false
	// insert left then right, this way when you parenthize left tree,
	// it will be paranthized normally, but when you paranthsize right tree with flag on
	// it will be reverse (aka equaling the left tree if they are mirror of each other.)
	bool is_symmetric_par() { // O(n) ~2n
		string left_tree = left->parenthesize();
		string right_tree = right->parenthesize();
		cout << left_tree << '\n' << right_tree;
		// if(left_tree.length() != right_tree.length())
		// 	return false;

		// int j = left_tree.size() - 1;
		// for(int i = 0; i < (int) left_tree.size(); i++) {
		// 	if(left_tree[i] != right_tree[j])
		// 		return false;
		// 	j--;
		// }
		return true;
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

	// not the best code, I tested it (a bit), but I'm not really sure
	// if it works 100% of the time or not.
	// welp I made the recursive way instead of the canonical way :cc
	bool is_flip_equiv(BinaryTree *other) {
		if(!other && !this)
			return true;
		if((!other && this) || (!this && other)) // one only
			return false;
		if(this->data != other->data)
			return false;
		if(!this->left && !this->right && !other->left && !other->right)
			return true;
		
		if(!other->left && other->right && this->left && !this->right)
			swap(this->left, this->right);
		else if(other->left && !other->right && !this->left && this->right)
			swap(this->left, this->right);
		else if(this->left && this->right && other->left && other->right && this->left->data != other->left->data)
			swap(this->left, this->right);

		return left->is_flip_equiv(other->left) && right->is_flip_equiv(other->right);
	}


	// well I missed the canonical part totally I guess.
	void print_duplicate_subtrees() { // O(n^3) :c
		string str1 = this->parenthesize();
		string str2 = str1;
		cout << str1 << '\n';
		this->print_preorder();
		// for(int i = 0; i < (int) str1.size(); i++) {
		// 	for(int j = 0; j < (int) str2.size(); j++) {
		// 		if(str1[i] == str2[j])
		// 	}
		// }
	}
};

void test_all_duplicates() {
	BinaryTree tree(1);
	/*
	tree.add( { 2, 4, 8 }, { 'L', 'L', 'L' });
	tree.add( { 2, 4, 9 }, { 'L', 'L', 'R' });
	tree.add( { 2, 5, 10 }, { 'L', 'R', 'L' });
	tree.add( { 2, 5, 11 }, { 'L', 'R', 'R' });

	tree.add( { 3, 6, 12 }, { 'R', 'L', 'L' });
	tree.add( { 3, 6, 13 }, { 'R', 'L', 'R' });
	tree.add( { 3, 7, 14 }, { 'R', 'R', 'L' });
	tree.add( { 3, 7, 15 }, { 'R', 'R', 'R' });
	tree.add( { 3, 7, 15, 16 }, { 'R', 'R', 'R', 'R' });
	*/

	tree.add( { 2, 3 }, { 'L', 'L'});
	tree.add( { 4, 5, 6, 8, 9 }, { 'R', 'R', 'R', 'R', 'R' });
	tree.add( { 4, 2, 3 }, { 'R', 'L', 'L'});
	tree.add( { 4, 5, 6, 7 }, { 'R', 'R', 'L', 'L'});
	tree.add( { 4, 5, 6, 8, 9 }, { 'R', 'R', 'L', 'R', 'R'});
	tree.add( { 4, 5, 6, 7 }, { 'R', 'R', 'R', 'L'});

	// (2(3()())())
	// (6(7()())(8()(9()())))
	// (8()(9()()))

	tree.print_duplicate_subtrees();
}

void tests_is_flip() {

	BinaryTree tree1(1);
	BinaryTree tree2(1);

	assert(tree1.is_flip_equiv(&tree2) == 1);

	// tree1.add({2, 3}, {'L', 'L'});
	// tree1.add({2, 3}, {'R', 'R'});
	// assert(tree1.is_flip_equiv(&tree2) == 0);

	tree1.add({3, 4}, {'L', 'L'});
	tree1.add({3, 5}, {'L', 'R'});
	tree1.add({2, 7}, {'R', 'L'});
	tree1.add({2, 6}, {'R', 'R'});

	tree2.add({2, 6}, {'L', 'L'});
	tree2.add({2, 7}, {'L', 'R'});
	tree2.add({3, 4}, {'R', 'L'});
	tree2.add({3, 5}, {'R', 'R'});

	assert(tree1.is_flip_equiv(&tree2) == 1);
	cout << "\n if seen -> works.\n";
}

void test1_is_symmetric() {
	BinaryTree tree(1);

	tree.add( { 2, 3 }, { 'L', 'L' });
	tree.add( { 2, 4, 5 }, { 'L', 'R', 'L' });
	tree.add( { 2, 4, 6 }, { 'L', 'R', 'R' });

	tree.add( { 2, 4, 6 }, { 'R', 'L', 'L' });
	tree.add( { 2, 4, 5 }, { 'R', 'L', 'R' });
	tree.add( { 2, 3 }, { 'R', 'R' });

	cout << tree.parenthesize();
}

int main() {
	// case 0
	BinaryTree tree(1);
	tree.add( { 2, 3 }, { 'L', 'L' });
	tree.add( { 2, 4, 5 }, { 'L', 'R', 'L' });
	tree.add( { 2, 4, 6 }, { 'L', 'R', 'R' });

	tree.add( { 2, 4, 6 }, { 'R', 'L', 'L' });
	tree.add( { 2, 4, 5 }, { 'R', 'L', 'R' });
	tree.add( { 2, 3 }, { 'R', 'R' });
	if(tree.is_bst1() == 1)
		cout << "SHIT!";
	else
		cout << "PHEW.";

	// case 0
	// tree.add({2}, {'L'});
	// tree.add({2}, {'R'});

	// // case 1
	// tree.add({2, 3}, {'L', 'L'});
	// tree.add({2, 4}, {'L', 'R'});
	// tree.add({2, 4}, {'R', 'L'});
	// tree.add({2, 3}, {'R', 'R'});

	// // case 1
	// tree.add({2, 3}, {'L', 'L'});
	// tree.add({2, 4}, {'L', 'R'});
	// tree.add({2, 4}, {'R', 'L'});
	// tree.add({2, 3}, {'R', 'R'});

	// tree.add({1, 2, 3, 4}, {'L', 'L', 'L', 'L'});

	// tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
	// tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
	// tree.add( { 2, 5, 9 }, { 'L', 'R', 'R' });
	// tree.add( { 3, 6, 10 }, { 'R', 'R', 'L' });

	// tree.add({1,2,3,4, 3}, {'L', 'R', 'R', 'R', 'R'});
	// tree.add({1,2,3}, {'L', 'L', 'L'});
	// tree.add({1,6,3}, {'L', 'R', 'L'});
	// tree.add({1,6,7,8, 3}, {'L', 'R', 'R', 'R', 'R'});
	// tree.add({4,6,7,8}, {'L','L','L','L'});



	// tree.print_inorder();
	// cout << '\n';
	// tree.print_inorder_iterative();
	// tree.print_test();
	// 7 4 8 2 5 9 1 3 10 6
	// cout << '\n';
	// cout << tree.tree_max();

	// cout << tree.tree_height();

	// cout << tree.count_nodes();

	// cout << tree.count_leaf();

	// if(tree.is_exist(4))
	// 	cout << "YES\n";
	// else
	// 	cout << "NO\n";

	// if(tree.is_perfect0())
	// 	cout << "YES\n";
	// else
	// 	cout << "NO\n";

	// tree.clear();
	// tree.check();
	// tree.print_inorder();

	// tree.traverse_left_boundry();

	// cout << tree.longest_path_length();
	// tree.level_print();
	// cout << '\n';
	// tree.test(tree.tree_height(), 0, 0);

	// tree.level_print();
	// cout << '\n';
	// tree.level_print_rec();
	// tree.level_order_traversal_spiral();

	// if(tree.is_complete())
	// 	cout << "YES\n";
	// else
	// 	cout << "NO\n";

	// test2_is_complete();
	// test1_level_order_traversal_spiral();

	// tree.print_inorder();
	// cout << '\n';
	// tree.print_preorder_complete();

	// if(tree.is_mirror(&tree, &tree))
	// 	cout << "YES\n";
	// else
	// 	cout << "NO\n";

	// tests_is_flip();
	// test_all_duplicates();
	test1_is_symmetric();
	cout << "\n NO R T E \n";
	return 0;
}

