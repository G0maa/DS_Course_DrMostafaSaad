#include<vector>
#include<iostream>
#include<cassert>
using namespace std;

class MaxHeap {
private:
	pair<int, int> *array; // was normal array
	int size { };
	int capacity { 1000 }; // kind of useless.

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
		if (child_pos == 0 || array[par_pos].second > array[child_pos].second) // <
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
		if (right_child != -1 && array[right_child].second > array[child_pos].second) // <
			child_pos = right_child;

		if (array[parent_pos].second < array[child_pos].second) { // >
			swap(array[parent_pos], array[child_pos]);
			heapify_down(child_pos);
		}
	}

	void heapify() {	// O(n)
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify_down(i);
	}

public:
	MaxHeap() {
		size = 0;
		array = new pair<int,int>[capacity];
	}

	MaxHeap(const vector<pair<int,int>> &v) {
		assert((int )v.size() <= capacity);
		array = new pair<int,int>[capacity];
		size = v.size();

		for (int i = 0; i < (int) v.size(); ++i)
			array[i] = v[i];

		heapify();
	}

	~MaxHeap() {
		delete[] array;
		array = nullptr;
	}

	void push(int key, int priority) {
		assert(size + 1 <= capacity);
		array[size++] = make_pair(key, priority);
		heapify_up(size - 1);
	}

	void pop() {
		assert(!isempty());
		size--;
		array[0] = array[size];
		heapify_down(0);
	}

	int top() {
		assert(!isempty());
		return array[0].first;
	}

	bool isempty() {
		return size == 0;
	}
};


int main() {
	// creat_heap_n();
	MaxHeap tasks;
	// Doctor's code:
	// he added one more array so it became int *key int & *value, kept the same code as before,
	// and just swapped both key & value when needed.
	// Again... I failed to observe such a thing which costed me a lot of time.
	tasks.push(1131, 1);
	tasks.push(3111, 3);
	tasks.push(2211, 2);
	tasks.push(3161, 3);
	tasks.push(7761, 7);


	cout << tasks.top() << "\n";
	tasks.pop();
	cout << tasks.top() << "\n";
	tasks.pop();

	tasks.push(1535, 1);
	tasks.push(2815, 2);
	tasks.push(3845, 3);
	tasks.push(3145, 3);

	while (!tasks.isempty()) {
		cout << tasks.top() << " ";
		tasks.pop();
	}
		
	cout << "\n NO RTE\n";
	return 0;
}
