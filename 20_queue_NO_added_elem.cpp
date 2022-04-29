#include <iostream>
#include <cassert>
using namespace std;

class Queue {
	int size { };
	int front { 0 };
	int rear { 0 };
	int *array { };

public:
	Queue(int size) :
			size(size) {
		array = new int[size];
		for(int i = 0; i < size; i++) // + hmmmmmmmmmm
			array[i] = -1;
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

	void enqueue(int value) {
		assert(!isFull());

		array[rear] = value;
		rear = next(rear);
	}

	int dequeue() {
		assert(!isEmpty());

		int value = array[front];
		array[front] = -1; // +
		front = next(front);
		return value;
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

		for (int cur = front, step = 0; array[cur] != -1 && step < size; ++step, cur = next(cur))
			cout << array[cur] << " ";
		cout << "\n\n";
	}

	int isEmpty() {
		return (rear == front && array[rear] == -1); // +
	}

	bool isFull() {
		return (rear == front && array[rear] != -1); // +
	}
};

int main() {
	// dr's solution added one element to the queue
	// made sure that we don't use that element,
	// therefore -> front == rear only when full.

    // When input is in a text file:
    // freopen("in.txt", "rt", stdin);
	freopen("out.txt", "wt", stdout);

	Queue qu(6);
	assert(qu.isEmpty());
	qu.display();

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isFull());
		qu.enqueue(i);
		qu.display();
	}
	assert(qu.isFull());

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isEmpty());
		qu.dequeue();
		//qu.display();
	}

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isFull());
		qu.enqueue(i);
		qu.display();
	}

	qu.dequeue();
	assert(!qu.isFull());
	qu.enqueue(7);
	assert(qu.isFull());
	qu.display();

	qu.dequeue();
	qu.dequeue();
	assert(!qu.isFull());
	qu.enqueue(8);
	assert(!qu.isFull());
	qu.display();
	qu.enqueue(9);
	assert(qu.isFull());
	qu.display();

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isEmpty());
		qu.dequeue();
		qu.display();
	}

	return 0;
}