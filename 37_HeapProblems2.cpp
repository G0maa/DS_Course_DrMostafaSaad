// Height -> ceil(log2(n+1) - 1)
// # of nodes in level i -> 2^i

// Two conditions of Binary Heap:
//      - Complete Binary Tree
//      - a node in the tree is <= all its children (root is min value)

// To get children of node i in Array reperesentation of Heap:
// i * 2 + 1 (first child), i * 2 + 1 (second child)
// As for parent of node i:
// floor((i - 1) / 2)

#include<vector>
#include<iostream>
#include<cassert>
using namespace std;

class MaxHeap {
private:
	int *array { };
	int size { };
	int capacity { }; // You can set this to K.

	int left(int node) {
		int p = 2 * node + 1;
		if (p >= size)
			return -1;
		return p;
	}
	int right(int node) {
		int p = 2 * node + 2;
		return p >= size ? -1 : p;
	}
	int parent(int node) {
		return node == 0 ? -1 : (node - 1) / 2;
	}

	void heapify_up(int child_pos) {
		// stop when parent is smaller (or no parent)
		int par_pos = parent(child_pos);
		if (child_pos == 0 || array[par_pos] > array[child_pos]) // <
			return;

		swap(array[child_pos], array[par_pos]);
		heapify_up(par_pos);
	}

	void heapify_down(int parent_pos) {	// O(logn)
		int child_pos = left(parent_pos);
		int right_child = right(parent_pos);

		if (child_pos == -1) // no children
			return;
		// is right smaller than left?
		if (right_child != -1 && array[right_child] > array[child_pos]) // <
			child_pos = right_child;

		if (array[parent_pos] < array[child_pos]) { // >
			swap(array[parent_pos], array[child_pos]);
			heapify_down(child_pos);
		}
	}

	void heapify() {	// O(n)
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify_down(i);
	}

public:
	MaxHeap(int k) {
        capacity = k;
		array = new int[capacity] { };
		size = 0;
	}

	~MaxHeap() {
		delete[] array;
		array = nullptr;
	}

	bool isempty() {
		return size == 0;
	}

   	void push(int key) {
		assert(size + 1 <= capacity);
		array[size++] = key;
		heapify_up(size - 1);
	}

	void pop() {
		assert(!isempty());
		array[0] = array[--size];
		heapify_down(0);
	}

	int top() {
		assert(!isempty());
		return array[0];
	}
	
    int next(int num) {
        if(size < capacity)
            push(num);
        else if(num < top()) {
			// Doctor's solution used pop() then push() directly,
			// which is a thing I failed to observe, but I think it's a correct soltuon nontheless.
			// My code is commented at end of this file.
			// This... costed me a lot of time.
			pop();
			push(num);
            // The code was bugged and I spent *some* time trying to figure out why : )
            // size = capacity;
        }
        return top();
    }
};

int main() {
    freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

    int k = 4;
	MaxHeap processor(k);

    int num;
    while(cin >> num)
        cout << processor.next(num) << '\n';
	cout << "\n NO RTE\n";
	return 0;
}


// else if(num < array[0]) {
// 			// Doctor's solution used pop() then push() directly,
// 			// which is a thing I failed to observe, but I think it's a correct soltuon nontheless.
//             while(size--) {
//                 swap(array[0], array[size]);
//                 heapify_down(0);
//                 if(array[0] >= num) {
//                     array[size] = num;
//                     heapify();
//                     break;
//                 }
//             }
//             // The code was bugged and I spent *some* time trying to figure out why : )
//             size = capacity;
//         }