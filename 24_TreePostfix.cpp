#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <stack>
using namespace std;

class BinaryTree {
private:
	string postfix { };
	BinaryTree* left { };
	BinaryTree* right { };

public:
	BinaryTree(string postfix) : postfix(postfix) {
		int len_postfix = (int) postfix.length();
		if(len_postfix == 1) // op or digit
			return;
		// I tried to shorten this code as much as I could.
		stack<BinaryTree*> st;
		for(int i = 0; i < len_postfix - 1; i++) {
			BinaryTree* node = new BinaryTree({postfix[i]});
			if(!(isdigit(postfix[i]))) {
				node->right = st.top(); st.pop();
				node->left = st.top(); st.pop();
			}
			st.push(node);
		}
		this->postfix = postfix[len_postfix - 1];
		this->right = st.top(); st.pop();
		this->left = st.top(); st.pop();
	}

	void print_inorder_expression() {
		// couldn't solve.
		// idea -> put () whenever you can as long as it's not leaf
		// ( -> call function -> )
		// the tree is orderd therefore it will put correct ()
	}

	void print_inorder() {
		if(left)
			left->print_inorder();
			
		cout << postfix;

		if(right)
			right->print_inorder();
	}
};

int main() {
	BinaryTree tree("534*2^+");
	tree.print_inorder();
	cout << "\n NO R T E \n";
	return 0;
}

