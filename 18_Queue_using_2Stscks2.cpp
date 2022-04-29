#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int top { };
	int* array { };
public:
	Stack(int size) :
			size(size), top(-1) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(int x) {
		assert(!isFull());
		array[++top] = x;
	}

	int pop() {
		assert(!isEmpty());
		return array[top--];
	}

	int peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}
};

class Queue {
	private:
		int size { };
		int added_elements { }; // revise use of this variable.
		Stack s1;
		Stack s2;
	public:

	Queue(int size) : size(size), added_elements(0), s1(size), s2(size) {

	}


	void enqueue(int val) { // O(1)
		assert(!s1.isFull());
		s1.push(val);
		added_elements++;
	}

	int dequeue() { // O(n) dr used one move, I used two.
		assert(!s1.isEmpty());
		while(!s1.isEmpty())
			s2.push(s1.pop());
		
		int val = s2.pop();

		while(!s2.isEmpty()) // I'll justifiy myself and say
			s1.push(s2.pop()); // this is an extra funcationaliy to make
							// display() eassier.
		added_elements--;
		return val;
	}

	void display() {
		assert(!s1.isEmpty());
		s1.display();
	}

	bool isEmpty() {
		return s1.isEmpty();
	}

	bool isFull() {
		return s1.isFull();
	}
};

int main() {

	Queue qu(6);

	for (int i = 1; i <= 3; ++i)
		qu.enqueue(i);

	cout<<qu.dequeue()<<" ";

	for (int i = 4; i <= 5; ++i)
		qu.enqueue(i);

	while(!qu.isEmpty())
		cout<<qu.dequeue()<<" ";
	return 0;
}
