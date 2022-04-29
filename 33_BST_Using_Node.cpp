// The lesson that should be learned is how to apply data structures using 1 class or 2 classes
// and the difference between them,
// here I kind-of completely used the wrong approach in solving that problem, 
// well not really wrong but not the intended way.

#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class BinarySearchTree {
private:
    struct BinaryNode {
        int data { };
        BinaryNode* left { };
        BinaryNode* right { };

        BinaryNode(int data) : data(data) { }
        BinaryNode(BinaryNode &another) {
            cout << "\nWARNING: A COPY HAPPENED HERE\n";
        }
    };
    BinaryNode* root { };

public:
    void insert_value(int target) {
        BinaryNode* new_node = new BinaryNode(target);
        if(!root) {
            root = new_node;
        }
        else {
            BinaryNode* last = nullptr;
            BinaryNode* cur = root;
            while(cur) {
                if(target > cur->data) {
                    last = cur;
                    cur = cur->right;
                }
                else if(target < cur->data) {
                    last = cur;
                    cur = cur->left;
                }
                else {
                    delete new_node;
                    return; // already exists.
                }    
            }

            if(target > last->data)
                last->right = new_node;
            else
                last->left = new_node;
        }
    }

    // these functions doesn't assume wrong input,
    // because public functions always call them with correct input only.
    BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

    void delete_no_child(BinaryNode &child, BinaryNode &parent) {
        if(child.data > parent.data)
            parent.right = nullptr;
        else
            parent.left = nullptr;
        delete &child;
    }

    void delete_one_child(BinaryNode &child, BinaryNode &parent) {
        if(child.data > parent.data)
            parent.right = (child.right) ? child.right : child.left;
        else
            parent.left = (child.right) ? child.right : child.left;
        delete &child;
    }
    // iterative, because head too small to handle recursion atm.
    void delete_node(int target) {
        if(target == root->data && !root->left && !root->right) {
            root = nullptr;
            return;
        }

        BinaryNode *child = root, *parent = nullptr;
        pair<BinaryNode*, BinaryNode*> two = search_delete(target, child, parent);
        child = two.first;
        parent = two.second;

        if(child) {
            if(!child->left && !child->right)
                delete_no_child(*child, *parent);
            else if(!child->left || !child->right)
                delete_one_child(*child, *parent);
            else {
                // delete_two_child(*child, *parent);
                BinaryNode *mn = min_node(child->right);
                int temp = mn->data;
                BinaryNode *node = child;
                // child->data = mn->data;
                parent = child;
                child = child->right;
                two = search_delete(mn->data, child, parent);
                if(two.first->right)
                    delete_one_child(*two.first, *two.second);
                else
                    delete_no_child(*two.first, *two.second);
                node->data = temp;
            }
        }
        // else -> doesn't exist.
	}

    pair<BinaryNode*, BinaryNode*> search_delete(int target, BinaryNode *child, BinaryNode *parent = nullptr) {
        while(child) {
            if(target > child->data) {
                parent = child;
                child = child->right;
            }
            else if(target < child->data) {
                parent = child;
                child = child->left;
            }
            else
                return make_pair(child, parent);
        }
        return make_pair(nullptr, nullptr);
    }

    bool search(int target) {
        if(!root)
            return false;
        BinaryNode* cur = root;
        while(cur) {
            if(target > cur->data)
                cur = cur->right;
            else if(target < cur->data)
                cur = cur->left;
            else
                return true;
        }
        return false;
    }

    void print_inorder(BinaryNode *node = nullptr, bool is_first_call = true) {
        // is this correct?
        if(is_first_call) {
            print_inorder(root, false);
            return;
        }

        if(!node)
            return;
        print_inorder(node->left, false);
        cout << node->data << ' ';
        print_inorder(node->right, false);
    }

    void give_inorder(vector<int> &values, BinaryNode *node = nullptr, bool is_first_call = true) {
        // is this correct?
        if(is_first_call) {
            give_inorder(values, root, false);
            return;
        }

        if(!node)
            return;
        give_inorder(values, node->left, false);
        values.push_back(node->data);
        give_inorder(values, node->right, false);
    }

// copy-paste old code + few changes
    void level_order_traversal() {
		queue<BinaryNode*> nodes_queue;
		nodes_queue.push(root);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout<<"Level "<<level<<": ";
			while(sz--) {
				BinaryNode* cur = nodes_queue.front();
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
};
BinarySearchTree* GetTree1();
void test2();

int main() {
    // BinarySearchTree *tree = GetTree1();
    // tree->print_inorder();

    // if(tree->search(74))
    //     cout <<"\nYES\n";
    // else
    //     cout <<"\nNO\n";

    // tree->level_order_traversal();

    test2();
    // BinarySearchTree *tree0 = GetTree1();
    // tree0->print_inorder();
    // cout << '\n';
    // tree0->delete_node(15); // doesn't work properly.
    // tree0->print_inorder();
    cout << "\nN/A(s) left his mark here.\n";
    return 0;
}


BinarySearchTree* GetTree1() {
    BinarySearchTree* tree = new BinarySearchTree();
    tree->insert_value(50);
    tree->insert_value(20);
	tree->insert_value(60);
	tree->insert_value(15);
	tree->insert_value(45);
	tree->insert_value(70);
	tree->insert_value(35);
	tree->insert_value(73);
	tree->insert_value(14);
	tree->insert_value(16);
	tree->insert_value(36);
	tree->insert_value(58);
	return tree;
}


// void test2() {
// 	BinarySearchTree* tree = GetTree1();

// 	vector<int> inorder;
// 	tree->give_inorder(inorder);

// 	for (int i = 0; i < (int) inorder.size(); ++i) {
// 		if (inorder[i] == 50)
// 			continue;	// root

// 		vector<int> inorder_v2;
// 		BinarySearchTree* tree = GetTree1();
// 		tree->delete_node(inorder[i]);
// 		tree->give_inorder(inorder_v2);

// 		vector<int> inorder_cpy = inorder;

// 		inorder_cpy.erase(find(inorder_cpy.begin(), inorder_cpy.end(), inorder[i]));
//         // for (int i = 0; i < inorder_cpy.size(); i++)
//         // {
//         //     cout << inorder_cpy[i] << ' ';
//         // }
//         // cout << '\n';
//         for (int i = 0; i < inorder_v2.size(); i++)
//         {
//             cout << inorder_v2[i] << ' ';
//         }
//         cout << '\n';
//         // break;
//         // cout << inorder[i] << " \n";
// 		assert(inorder_cpy == inorder_v2);
// 		// if(inorder_cpy != inorder_v2) {
//         //     cout << inorder[i] << '\n';
//         //     for (int i = 0; i < inorder_cpy.size(); i++)
//         //     {
//         //         cout << inorder_cpy[i] << ' ';
//         //     }
//         //     cout << '\n';
//         //     for (int i = 0; i < inorder_v2.size(); i++)
//         //     {
//         //         cout << inorder_v2[i] << ' ';
//         //     }
//         // }
// 	}
// }

void test2() {
	BinarySearchTree* tree = GetTree1();

	vector<int> inorder;
	tree->give_inorder(inorder);

	for (int i = 0; i < (int) inorder.size(); ++i) {
		// if (inorder[i] == 50)
		// 	continue;	// root

		vector<int> inorder_v2;
		BinarySearchTree* tree = GetTree1();
		tree->delete_node(inorder[i]);
		tree->give_inorder(inorder_v2);

		vector<int> inorder_cpy = inorder;
		inorder_cpy.erase(find(inorder_cpy.begin(), inorder_cpy.end(), inorder[i]));
		assert(inorder_cpy == inorder_v2);
	}
}