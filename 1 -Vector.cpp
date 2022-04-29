#include <iostream>
#include <cassert>
using namespace std;

class Vector {
private:
	int *arr { nullptr };
	int size { 0 };			// user size
	int capacity { };		// actual size

	void expand_capacity() {
		// Double the actual array size
		capacity *= 2;
		cout << "Expand capacity to "
				<< capacity << "\n";
		int *arr2 = new int[capacity] { };
		for (int i = 0; i < size; ++i)
			arr2[i] = arr[i];	// copy data

		swap(arr, arr2);
		delete[] arr2;
	}

public:


	Vector(int size) :
			size(size) {
		if (size < 0)
			size = 1;
		capacity = size + 10;
		// The actual size array will
		// be bigger than needed
		arr = new int[capacity] { };
	}

	~Vector() {
		delete[] arr;
		arr = nullptr;
	}

	int get_size() {
		return size;
	}

	int get(int idx) {
		assert(0 <= idx && idx < size);
		return arr[idx];
	}

	void set(int idx, int val) {
		assert(0 <= idx && idx < size);
		arr[idx] = val;
	}

	void print() {
		for (int i = 0; i < size; ++i)
			cout << arr[i] << " ";
		cout << "\n";
	}

	int find(int value) {
		for (int i = 0; i < size; ++i)
			if (arr[i] == value)
				return i;
		return -1;	// -1 for NOT found
	}

	int get_front() {
		return arr[0];
	}

	int get_back() {
		return arr[size - 1];
	}

	void push_back(int value) {
		// we can't add any more
		if (size == capacity)
			expand_capacity();
		arr[size++] = value;
	}
	void insert(int idx, int value) {
		assert(0 <= idx && idx < size);

		// we can't add any more
		if (size == capacity)
			expand_capacity();

		// Shift all the data to right first

		for(int p = size-1; p >= idx; --p)
			arr[p+1] = arr[p];

		arr[idx] = value;
		++size;

		// Common mistake to iterate from begin to end
		// the whole array right array will be arr[idx]
		//for (int p = idx; p < size; ++p)
	}

	void right_rotate() {
		for(int i = size - 1; i > 0; i--) { // Doctor didn't use swap.
			swap(arr[i], arr[i - 1]);
		}
		return;
	}

	void left_rotate() {
		for(int i = 0; i < size; i++) {
			swap(arr[i], arr[i + 1]);
		}
		return;
	}

	void right_rotate_n(int times) {
		int ans = times % size;
		for(int i = 0; i < times; i++)
			right_rotate();
		return;
	}

	int pop(int idx) {
		int element = arr[idx];
		arr[idx] = 0; // or -1 depedning on the initial value of the data structure
		for(int i = idx; i < size; i++) {
			swap(arr[i], arr[i + 1]);
		}
		size--;
		return element;
	}

	int find_transposition(int value) {
		int ans = find(value);
		if(ans != 0) {
			swap(arr[ans], arr[ans - 1]);
			return ans - 1;
		}
		else if(ans == -1)
			return -1;
		return 0;
	}
};

int main() {

	int n = 5;
	Vector v(n);
	for (int i = 0; i < n; ++i)
		v.set(i, i);

	v.right_rotate();
	v.print();

	return 0;
}
