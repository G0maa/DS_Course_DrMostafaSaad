// Mistake -> I edited Queue functions while I should have not done so.
#include <iostream>
#include <cassert>
using namespace std;

class Queue {
	int size { };
	int front { 0 };
	int rear { 0 };
	int added_elements { };
	int *array { };

public:
	Queue(int size) :
			size(size) {
		array = new int[size];
	}

	~Queue() {
		delete[] array;
	}

	int next(int pos) {
		++pos;
		if (pos == size)
			pos = 0;
		return pos;
		//return (pos + 1) % size;	//  Or shorter way
	}

	int before(int pos) {
		--pos;
		if (pos == -1)
			pos = size - 1;
		return pos;
	}

	void enqueue(int value) {
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	int dequeue() { // edited for stack
		assert(!isEmpty());
		rear = before(rear);
		int value = array[rear];
		--added_elements;
		return value;
	}

	int peek() {
		assert(!isEmpty());
		return array[before(rear)];
	}

	void display() {
		cout << "Front " << front << " - rear " << rear << "\t";
		if (isFull())
			cout << "full";
		else if (isEmpty()) {
			cout << "empty\n\n";
			return;
		}
		cout << "\n";

		for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
			cout << array[cur] << " ";
		cout << "\n\n";
	}

	int isEmpty() {
		return added_elements == 0;
	}

	bool isFull() {
		return added_elements == size;
	}
};

class Stack {
	private:
		Queue q;
		int added_elements { };
	public:

		Stack(int size) : added_elements(0), q(size){ }

		void push(int val) { // should have came for an idea
			q.enqueue(val); // in it here, not change the function in Queue
			added_elements++; // smh.
		}

		int pop() {
			int val = q.dequeue();
			added_elements--;
			return val;
		}

		int peek() {
			return q.peek();
		}

		bool isFull() {
			return q.isFull();
		}

		bool isEmbty() {
			return q.isEmpty();
		}
};

int main() {
	
	Stack stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);

	// cout << stk.pop() << ' ';
	// cout << stk.pop() << ' ' << stk.pop();;

	while(!stk.isEmbty()) {
		cout << stk.peek() << ' ';
		stk.pop();
	}

	cout << "\n NO R T E \n";
	return 0;
}
