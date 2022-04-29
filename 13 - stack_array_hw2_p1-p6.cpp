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

	int pop() { // changed this to return 0 for #HW2-P5
		if(isEmpty()) return 0;
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

	// HW2-P2- O(N) both time & memory
	void insert_at_bottom(int x) {
		assert(!isFull()); // when embty?

		if(isEmpty()) {
			push(x);
			return;
		}
		int temp = pop();
		insert_at_bottom(x);
		push(temp);
	}

	void stack_reverse() { // I think O(n^2) time & memory ~O(2n)?
		if(isEmpty())
			return;
		int temp = pop();
		stack_reverse();
		insert_at_bottom(temp);
	}

	void check() {
		cout << array[0] << '\n';
	}
};

void astroid_collision(int n) { // Took tooooooooooooooo much time in this one :c
	int x;						// I have no comments.
	Stack stk(n);
	for(int i = 0; i < n; i++) {
		cin >> x;
		while(!stk.isEmpty() && (stk.peek() > 0 && x < 0) && (abs(stk.peek()) < abs(x))) {
			stk.pop();
		} // While stack isn't embty and peek() and x go >< and peek is less than x.

		if(stk.isEmpty() || !(stk.peek() > 0 && x < 0)) // no-clean :c
			stk.push(x);
		else if(abs(stk.peek()) == abs(x)) // if bigger -> no push
			stk.pop();	
	}

	// Just printing in an elegant way : ) Were there a better way? I don't know.
	int ans[n], i;
	for(i = n - 1; i >= 0 && !stk.isEmpty(); i--)
		ans[i] = stk.pop();
	i++;
	cout << '[';
	for(i; i < n; i++) {
		cout << ans[i];
		if((i < n - 1))
			cout << ", ";
	}
	cout << ']';
}

void fact(int n) { // HW2-P4 -> Very wrong solution :c
	// tl;dr of dr's solution:
	// You have a stack of "StackElement", you push to it StackElement(n), which isn't computed (see function)
	// then in the while loop you will keep pushing of Stackelemnts of peek() - 1, until you reach n = 1,
	// therefore it is the base case which you will make it's result computed -> cur.n = 1
	// after that since you got one computed you will compute the rest, pop the peek and it's parent, muliply results, push the parent with it's result
	// if embty -> you got the needed answer.
	Stack stk(n);
	while(n > 1) {
		stk.push(n);
		n--;
	}

	int ans = 1;
	while(!stk.isEmpty())
		ans *= stk.pop();

	cout << ans;
}

int score_parent(string s) { // HW2-P5 Beautiful solution? O(n)
							// nvm dr's code is cleaner, similar solution though : )
	int len_s = s.length(), temp;
	Stack stk(len_s); // len_s / 2?

	bool rep_pop = false;
	for(int i = 0; i < len_s; i++) {
		if(s[i] == '(') {
			rep_pop = false;
			stk.push(0);
		} else {
			if(!rep_pop) {
				temp = stk.pop() + stk.pop() + 1;
				rep_pop = true;
			}
			else
				temp = (stk.pop() * 2) + stk.pop();
			stk.push(temp);
		}
	}
	return stk.pop();
}

void next_greater_element(int v[], int len) {
	// >> I was not able to solve this one. <<
	// tl;dr of the solution:
	// You have a stack for position, imagine beign in the middle of a soluton,
	// there are positions before you and you are v[i]
	// you will iterate over everything in the stack, if you are bigger, you will pop it,
	// and set it's index to be equal to you, if you are not bigger you will stop.
	// Stack always has elements which are not fullfilled yet.
	Stack pos(len);
	for (int i = 0; i < (int) len; ++i) {
		while (!pos.isEmpty() && v[i] > v[pos.peek()])
			v[pos.pop()] = v[i];
		pos.push(i);
	}

	while (!pos.isEmpty())
		v[pos.pop()] = -1;

	for (int i = 0; i < (int) len; ++i)
		cout << v[i] << " ";
	cout<<"\n";
}

int main() {


	// astroid_collision(3);

	// Stack stk(4);
	// stk.push(3);
	// stk.push(2);
	// stk.push(1);
	// stk.insert_at_bottom(4);
	// stk.display();
	// stk.stack_reverse();
	// stk.display();

	// fact(5);

	cout << score_parent("()(()(()))") << '\n';
	cout << "\n\n NO R  T  E\n\n";
	return 0;
}
