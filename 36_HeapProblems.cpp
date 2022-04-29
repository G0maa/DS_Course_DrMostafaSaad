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

    // HW: Find smaller values: (integrity will get void tho)
	// Doctor's idea -> recursively check every left and right child, if less print it, if bigger return. (Recurse like VLR)
	// Ordering isn't important as said in the problem.
    void print_less_than(int val, int parent_pos = 0) {
        while(top() < val) {
            cout << top() << ' ';
            pop();
        }
    }

    // recursion at work : )
	// If given tree(array) isn't complete => there will be missing children.
	// Doctor's solution => interface function which takes internal array and size in two varaibles,
	// call private function is_heap, is_heap does the same as this one but with calling left() and right() directly.
    bool is_heap_array(int *arr, int n, int i = 0) {
        if(i >= n)
            return true;
        
        if(i * 2 + 1 < n)
            if(arr[i * 2 + 1] < arr[i])
                return false;

        if(i * 2 + 2 < n)
            if(arr[i * 2 + 2] < arr[i])
                return false;

        return is_heap_array(arr, n, i + 1) && is_heap_array(arr, n, i + 2);
    }

    // Heap sort:

	int left(int node, int n) {
		int p = 2 * node + 1;
		if (p >= n)
			return -1;
		return p;
	}
	int right(int node, int n) {
		int p = 2 * node + 2;
		return p >= n ? -1 : p;
	}

	// void heapify_up(int child_pos) {
	// 	// stop when parent is smaller (or no parent)
	// 	int par_pos = parent(child_pos);
	// 	if (child_pos == 0 || array[par_pos] < array[child_pos])
	// 		return;

	// 	swap(array[child_pos], array[par_pos]);
	// 	heapify_up(par_pos);
	// }

	void heapify_down(int parent_pos, int *arr, int n) {	// O(logn)
		int child_pos = left(parent_pos, n);
		int right_child = right(parent_pos, n);

		if (child_pos == -1) // no children
			return;
		// is right smaller than left?
		if (right_child != -1 && arr[right_child] < arr[child_pos])
			child_pos = right_child;

		if (arr[parent_pos] > arr[child_pos]) {
			swap(arr[parent_pos], arr[child_pos]);
			heapify_down(child_pos, arr, n);
		}
	}

	// I was close, actually very close, but I was too tired, too hopeless sadly, anyway
	// Doctor's solution has the same idea,
	//  of heapify() then swap() and heaspify_down(), after that he reversed the array.
	// but before all of this,
	//  he saved current MinHeap array & size in variables,
	//  and put arr & n in the old variables (MinHeap) varaibles.
    void heap_sort(int *arr, int n) {
		// heapify
		for (int i = n / 2 - 1; i >= 0; --i)
			heapify_down(i, arr, n);

		for(int i = 0; i < 14; i++)
			cout << arr[i] << ' ';

		int arr_size = n;
		for(int i = 0; i < n; i++) {
			swap(arr[0], arr[arr_size - 1]);
			heapify_down(0, arr, arr_size - 1);
			arr_size--;
		}
    }

	void test() {
		for(int i = 0; i < 14; i++)
			cout << array[i] << ' ';
	}
};

void creat_heap_nlogn() {
	MinHeap heap;

	vector<int> v { 2, 17, 22, 10, 8, 37,
		14, 19, 7, 6, 5, 12, 25, 30 };

	for (int i = 0; i < v.size(); ++i)
		heap.push(v[i]);

	// heap.test();
	// while (!heap.isempty()) {
	// 	cout << heap.top() << " ";
	// 	heap.pop();
	// }
	// 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}

void creat_heap_n() {
	vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MinHeap heap(v);

	while (!heap.isempty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
}

void is_heap_array() {
	vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MinHeap heap(v);

	int arr[] {2, 5, 12, 7,6, 22, 14, 19, 10, 17, 8, 37, 25, 30};
	cout<<heap.is_heap_array(arr, 14)<<"\n";	// 1
	swap(arr[0], arr[5]);
	cout<<heap.is_heap_array(arr, 14)<<"\n";	// 0
}

int main() {
	is_heap_array();
	// creat_heap_nlogn();
	// creat_heap_n();
    // MinHeap heap;

    // if(heap.is_heap_array(v, 14))
    //     cout << "YES\n";
    // else
    //     cout << "NO\n";
    // heap.heap_sort(v, 14);
    // for (int i = 0; i < 14; i++)
    // {
    //     cout << v[i] << ' ';
    // }
	// { 2, 5, 12, 7, 6, 22, 14, 19, 10, 17, 8, 37, 25, 30 }
			  
	int v[] = { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MinHeap test;
	test.heap_sort(v, 14);
	// for(int i = 0; i < 14; i++)
	// 	cout << v[i] << ' ';
    cout << "\n NO RTE\n";
	return 0;

}