#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
	int size { };
	int added_elements = 0;
	int* array { };
public:
	Stack(int size) :
			size(size) {
		array = new int[size];
	}

	~Stack() {
		delete[] array;
	}

	bool push(int x) { // O(n)
		if(isFull())
			return false;
		
		for(int i = added_elements; i > 0; i--) {
			swap(array[i], array[i - 1]); // I should probably stop using swap()
		}
		array[0] = x;
		added_elements++;
		return true;
	}

	bool pop() { // O(n)
		if(isEmpty())
			return false;
		for(int i = 0; i < added_elements; i++)
			swap(array[i], array[i + 1]);
		added_elements--;
		return true;
	}

	int peek() {
		if(isEmpty())
			return false;
		return array[0];
	}

	bool isFull() {
		return added_elements == size;
	}

	bool isEmpty() {
		return added_elements == -1;
	}

	void display() {
		for (int i = 0; i < added_elements; i++)
			cout << array[i] << " ";
		cout << "\n";
	}
};

int main() {

	Stack stk(5);
	stk.push(5);
	// stk.push(4);
	// stk.push(3);
	// stk.push(2);
	// stk.push(1);
	// stk.push(1);
	stk.pop();
	stk.pop();
	stk.display();
	
	cout << "\n\n NO R T E \n\n";
	return 0;
}
