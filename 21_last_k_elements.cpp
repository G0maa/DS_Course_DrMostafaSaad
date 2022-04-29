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
		// assert(!isEmpty());
		if(added_elements < 4) // just for this problem to make it much easier.
			return 0;
		int value = array[front];
		front = next(front);
		--added_elements;
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

class p3 {
	private:
		Queue q;
		int k = { };
		int ans = { };

	public:
		p3(int k) : k(k), q(k + 1) { }

		int next(int new_num) {
			ans -= q.dequeue();
			ans += new_num;
			q.enqueue(new_num);
			return ans;
		}
};

int main() {
	// I improvised a lot I guess :)
	freopen("in.txt", "rt", stdin);
	freopen("out.txt", "wt", stdout);
	p3 processor(4);

	int num;
	while(cin >> num)
		cout << processor.next(num) << '\n';
	return 0;
}