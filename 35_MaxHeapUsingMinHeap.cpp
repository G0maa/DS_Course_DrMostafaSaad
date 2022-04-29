#include<vector>
#include<iostream>
#include<cassert>
using namespace std;

class MinHeap {
private:
	int *array { };
	int size { };
	int capacity { 1000 };

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
		if (child_pos == 0 || array[par_pos] < array[child_pos])
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
		if (right_child != -1 && array[right_child] < array[child_pos])
			child_pos = right_child;

		if (array[parent_pos] > array[child_pos]) {
			swap(array[parent_pos], array[child_pos]);
			heapify_down(child_pos);
		}
	}

	void heapify() {	// O(n)
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify_down(i);
	}

public:
	MinHeap() {
		array = new int[capacity] { };
		size = 0;
	}

	MinHeap(const vector<int> &v) {
		assert((int )v.size() <= capacity);
		array = new int[capacity] { };
		size = v.size();

		for (int i = 0; i < (int) v.size(); ++i)
			array[i] = v[i];

		heapify();
	}

	~MinHeap() {
		delete[] array;
		array = nullptr;
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

	bool isempty() {
		return size == 0;
	}
	friend class MaxHeap;
};

// Idea: Any sorting algrotihm that sorts from bigger to smaller can be switched,
// 		 when you muliply numbers with -1, use the algorithm, then mulitply them with -1 again.
// 		 so pushing with key * -1, top & pop key * -1 also.
class MaxHeap {
private:
    MinHeap heap;
public:
    MaxHeap() : heap(){ } // ???

    MaxHeap(const vector<int> &v) : heap(v) { }

    ~MaxHeap() {
        delete &heap; // << Probably not correct.
    }

	void push(int key) {
		heap.push(key);
	}

	void pop() {
		assert(!isempty());
		--heap.size;
	}

    int top() {
        return heap.array[heap.size - 1];
    }

    bool isempty() {
        return heap.isempty();
    }
};

void creat_heap_nlogn() {
	MaxHeap heap;

	vector<int> v { 2, 17, 22, 10, 8, 37,
		14, 19, 7, 6, 5, 12, 25, 30 };

	for (int i = 0; i < v.size(); ++i)
		heap.push(v[i]);

	while (!heap.isempty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
	// 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}

void creat_heap_n() {
	vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MaxHeap heap(v);

	while (!heap.isempty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
}

int main() {
	creat_heap_nlogn();

	cout << "\n\n NO RTE \n\n";
	return 0;

}
