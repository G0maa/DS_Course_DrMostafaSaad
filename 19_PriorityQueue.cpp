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

	void enqueue(int value) {
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	int dequeue() {
		assert(!isEmpty());
		int value = array[front];
		front = next(front);
		--added_elements;
		return value;
	}

	void display() { // I had to comment those lines *shrug*
		// cout << "Front " << front << " - rear " << rear << "\t";
		// if (isFull())
		// 	cout << "full";
		// else if (isEmpty()) {
		// 	cout << "empty\n\n";
		// 	return;
		// }
		// cout << "\n";

		for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
			cout << array[cur] << " ";
		cout << "\n";
	}

	int isEmpty() {
		return added_elements == 0;
	}

	bool isFull() {
		return added_elements == size;
	}
};

class PriorityQueue {
	private:
		Queue q1, q2, q3;
		int size = { };
		// no added_elements variable here. -
	public:

	PriorityQueue(int size) : size(size), q1(size),
							 q2(size), q3(size) { }

	void enqueue(int task, int priority) {
		if(priority == 3) {
			q3.enqueue(task);
		}
		else if(priority == 2) {
			q2.enqueue(task);
		}
		else if(priority == 1) {
			q1.enqueue(task);
		}
		else
			cout << "OoF -> Out of priority m8.";
	}

	int dequeue() {
		assert(!isEmbty());
		int val;
		if(!q3.isEmpty()) {
			val = q3.dequeue();
		}
		else if(!q2.isEmpty()) {
			val = q2.dequeue();
		}
		else {
			val = q1.dequeue();
		}
		return val;
	}

	void display() {
		if(!q3.isEmpty()) {
			cout << "Priority #3 tasks: ";
			q3.display();
		}

		if(!q2.isEmpty()) {
			cout << "Priority #2 tasks: ";
			q2.display();
		}

		if(!q1.isEmpty()) {
			cout << "Priority #1 tasks: ";
			q1.display();
		}
	}

	bool isFull() {
		return q1.isFull() || q2.isFull() || q3.isFull();
	}

	bool isEmbty() {
		return (q1.isEmpty() == 1 && q2.isEmpty() ==  1 && q3.isEmpty() == 1);
	}

};

int main() {
	
	PriorityQueue tasks(8);

	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);

	tasks.display();

	cout << tasks.dequeue() << '\n';
	cout << tasks.dequeue() << '\n';

	tasks.enqueue(1535, 1);
	tasks.enqueue(2815, 2);
	tasks.enqueue(3845, 3);
	tasks.enqueue(3145, 3);
	
	tasks.display();

	while(!tasks.isEmbty())
		cout << tasks.dequeue() << ' ';
	return 0;
}
