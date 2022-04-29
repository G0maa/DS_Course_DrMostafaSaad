#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
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
		if(isEmpty()) // edited this for p4
			return false;
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

	// p2
	string reverse_subwords(string line) { // added dummy space :c
		int len_line = line.length(), idx = 0, here;
		// just making sure we have enough elements in the array.
		int *new_arr = new int [len_line];
		size = len_line;
		swap(array, new_arr);
		delete[] new_arr;

		while(idx < len_line) { // True that it is 3 loops, but same
			here = idx; // complexity as in the solution (I think)
			while(here < len_line && line[here] != 32) { // this one is uselss.
				push(line[here]);
				here++;
			}

			while(idx != here) { // < ?
				line[idx] = pop();
				idx++;
			}
			idx++; // for the extra space
		}
		return line;
	}

	int reverse_num(int num) { // same solution, but his is a bit more cleaner.
		int new_len = log10(num) + 1;

		int *new_arr = new int [new_len];
		size = new_len;
		swap(array, new_arr);
		delete[] new_arr;

		while(num > 0) {
			push(num % 10);
			num /= 10;
		}

		int i = 1;
		while(!isEmpty()) {
			num += pop() * i;
			i *= 10;
		}
		return num;
	}

	bool isValid(string str) { // Same idea minus the clean code.
		int len_str = str.length(), idx = 0;

		int *new_arr = new int [len_str];
		size = len_str;
		swap(array, new_arr);
		delete[] new_arr;

		while(idx < len_str) {
			if(str[idx] == 40 || str[idx] == 91 || str[idx] == 123) {
				push(str[idx]);
				idx++;
			} else {
				if(((str[idx] == 125 && peek() == 123)) 
					|| (str[idx] == 93 && peek() == 91)
					|| (str[idx] == 41 && peek() == 40)) {
						pop();
						idx++;
					}
				else
					return false;
			}
		}
		if(isEmpty())
			return true;
		else
			return false;
	}

	string removeDuplicates(string s) {
		int len_s = s.length(), idx = 0;

		int *new_arr = new int [len_s];
		size = len_s;
		swap(array, new_arr);
		delete[] new_arr;

		while(idx < len_s) {
			if(s[idx] == peek()) {
				pop();
			}
			else
				push(s[idx]);
			idx++;
		}
		
		// This part here is inefficient, I should have just did
		// temp = stk.pop() + temp;
		string temp = "";
		for(int i = 0; i <= top; i++)
			temp+= '0';

		while(!isEmpty()) {
			char c = peek();
			temp[top] = c;
			pop();
		}
		return temp;
	}

};

int main() {


	Stack stk(10);
	cout << stk.removeDuplicates("ccbaacacbb");

	return 0;
}
