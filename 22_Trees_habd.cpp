// Lots of information in the videos,
// not sure if I got all of it, but they're all easy anyway (I think).
#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
#include <queue>>
using namespace std;

struct Node {
	int data { };
	Node* left { };
    Node* right { };

	Node(int data) : data(data) { }
};

class BinaryTree {
    private:
        int data { };
        BinaryTree *left { };
        BinaryTree *right { };
public:

    BinaryTree(int data) : data(data) { }

    // You have to go in the correct order when inserting the nodes tho,
    // simple functions doesn't deal with much edge-cases,
    // and not tested well >_>.
    void add(vector<int> &path_nodes, string &directions) {
        if((int) path_nodes.size() != (int) directions.size()) {
            cout << "Pahts are not of the same size.\n";
            return;
        }
        else {
            BinaryTree *cur = this; // check if null?
            int i;
            for(i = 0; i < (int) directions.size() - 1; i++) { // -1
                cur = directions[i] == 'L' ? cur->left : cur->right;
                if(!cur || cur->data != path_nodes[i])
                    cout << "Non-existent node or wrong path_nodes.\n";
            }
            BinaryTree *new_Binary_tree = new BinaryTree(path_nodes[i]);

            directions[i] == 'L' ? cur->left = new_Binary_tree : cur->right = new_Binary_tree;
            // if(directions[i] == 'L')
            //     cur->left = new_Binary_tree;
            // else
            //     cur->right = new_Binary_tree;
        }
    }

    

    void check() {
        cout << this->left->data << ' ';
    }
};
// Traverseing BTs:
// in-order: LVR
// post-order: LRV
// pre-order: VLR

// BTs Types:
// Full (strict) BT, each node has 0 or 2 children. (or k-ary tree when chuildren are 3+)
//  - leaf_nodes = internal_nodes + 1.
//  - minimum # of nodes in it -> 2*h+1.
// Perfect BT, all leaf nodes have the same level, all other nodes have 2 children.
// Complete BT (variant of ^), but last level is filled from left to right with possibily some missing nodes.
// - a perfect BT is a complete BT/Full BT.
// Degenerate Tree, Each nodes has only one child.
// A balanced BT -> left sub-tree & right-sub-tree difference in height is 0 or 1 (<= 1), goes rucrseively for rest of sub-tres.

// levels, 0 indexed start from root -> root level 0.
// height how many edges from root to the furthest leaf. (levels - 1 ?mostly?)

// BTs Formulas:
// In a perfect tree, 
//  - # of nodes -> 2^levels - 1,
//  - find height using # of nodes -> h = log(n + 1) - 1.
// there's some other facts that I am lazy to write.
// ceil(log leaves)  + 1 = min # level

// how many labeled trees of n nodes? (2n)! / (n + 1)! (for un labeled divide by n!).



void printt(Node *root) { // BFS?
    // if is root print myself, but we don't have that currently I guess.
    if(!root)
        return;
    
    if(root -> left)
        cout << root -> left -> data << ' ';
    if(root -> right)
        cout << root -> right -> data << ' ';
    
    printt(root -> left);
    printt(root -> right);
}



// as for representing a tree using array, I saw it before in
// one of the videos, I think you will have each parent child child,
// going through each level this meanas you will have more, parent child child, parent child child,
// and so on, so each time you go 2^i+1.
// obviously this is very inefficient if tree isn't full.

void clear(Node *current) {
    if(!current)
        return;

    clear(current->left);
    clear(current->right);
    delete current;
}

int main() {

    BinaryTree root(4);
    string test = "L";
    vector<int> test_vec {2};
    root.add(test_vec, test);

    root.check();
    cout << "\n NO RTE \n";
	return 0;
}


// class Binary_Tree {
//     private:
//         Node* root { };
//         // we can have arr for parents to make traverseing easier.
//         // this here just a 10 minute thinking of binary_tree code,
//         // got ahead of myself I guess with the thinking process. :D
//     public:

//     void add(Node* new_node) {
//         if(!root) {
//             root = new_node;
//             return;
//         }
//         // Node* cur = root;
//         // while(cur -> left || root -> right) {
//         //     if(!(cur -> left))
//         //         cur -> left = new_node;
//         //         return;
//         //     else if(!(cur -> right)) {
//         //         cur -> right = new_node;
//         //         return;
//         //     }

//         //     cur = cur -> left;
//         // }
//     }
// };

    // Node* root = new Node(1);
	// Node* node2 = new Node(2);
	// Node* node3 = new Node(3);
	// Node* node4 = new Node(4);
	// Node* node5 = new Node(5);
	// Node* node6 = new Node(6);
	// Node* node7 = new Node(7);
	// Node* node8 = new Node(8);

    // root->left = node2;
	// root->right = node3;

	// node2->left = node4;
	// node2->right = node5;

	// node5->right = node7;

	// node3->right = node6;

	// node6->left = node8;

    // printt(root);
    // clear(root);
    // printt(root);