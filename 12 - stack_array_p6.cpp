// Conclusion for this homework from p1-p6:
// I should have created functions outside of the classs
// most solutions have the same idea & complexity (but one)
// but not as clean as they could be.

#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int top1 { };
	int top2 { };
	int* array { };
public:
	Stack(int size) :
			size(size), top1(-1), top2(size) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(int id, int x) {
		assert(!isFull());
		if(id == 1)
			array[++top1] = x;
		else
			array[--top2] = x;
	}

	int pop(int id) {
		if(id == 1) {
			assert(!isEmpty(1));
			return array[top1--];
		} else {
			assert(!isEmpty(2));
			return array[top2++];
		}
	}

	int peek(int id) {
		
		if(id == 1) {
			assert(!isEmpty(1));
			return array[top1];
		} else {
			assert(!isEmpty(2));
			return array[top2];
		}			
	}

	int isFull() {
		return top1 + 1 + (size - top2) == size;
	}

	int isEmpty(int id) {
		if(id == 1)
			return top1 == -1;
		else
			return top2 == size + 1;
	}

	void display() {
		for (int i = top1; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
		for(int i = top2; i < size; i++)
			cout << array[i] << ' ';
		cout << '\n';
	}
};

int main() {

	Stack stk(10);
	stk.push(2, 5);
	stk.push(2, 6);
	stk.pop(2);
	stk.push(2, 7);
	stk.push(2, 9);

	stk.push(1, 4);
	cout << stk.peek(1) << '\n';
	cout << stk.peek(2) << '\n';
	stk.push(1, 6);
	stk.push(1, 8);
	stk.push(2, 3);

	cout << "\n\n NO R T E \n\n";
	return 0;
}
