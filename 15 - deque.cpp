#include <iostream>
#include <cassert>
using namespace std;

class Deque {
	int size { };
	int front { 0 };
	int rear { 0 };
	int added_elements { };
	int *array { };

public:
	Deque(int size) :
			size(size) {
		array = new int[size];
	}

	~Deque() {
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

	void enqueue_rear(int value) {
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	void enqueue_front(int val) {
		assert(!isFull());
		front = before(front);
		array[front] = val;
		added_elements++;
	}

	int dequeue_front() {
		assert(!isEmpty());
		int value = array[front];
		front = next(front);
		--added_elements;
		return value;
	}

	int dequeue_rear() {
		assert(!isEmpty());
		rear = before(rear);
		int value = array[rear];
		added_elements--;
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

int main() {

	Deque dq(6);
	dq.enqueue_front(3);
	dq.enqueue_front(2);
	dq.enqueue_rear(4);
	dq.enqueue_front(1);
	dq.display();

	cout << dq.dequeue_rear() << '\n';
	dq.display();
	cout << dq.dequeue_front() << '\n';
	dq.display();

	cout << dq.dequeue_rear() << '\n';
	cout << dq.dequeue_front() << '\n';
	dq.enqueue_rear(7);
	dq.display();
	cout << "\n NO R T E \n";
	return 0;
}
