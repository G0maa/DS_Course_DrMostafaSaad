// O(1) both array & linkedlist
// Size for linkdlist, I don't think random access is an avantage for arrays
// I think generally linked list might be a better implementation for Stack
// maybe reverse and inert at bottom are easier?

// This round for HW was kind of bad, I didn't know how to solve two problems,
// and 2 solutions of the solved ones were wrong.
// and I easily forgot the solutions. :c
// there's no clear reason really, I gave each problem its time.

#include <iostream>
#include <cassert>
#include <climits>
#include <cmath>
using namespace std;

class Stack {
private:
	// Tip: We can make this struct internally
	struct Node {
		double data { }; // was int
		Node* next { };
		Node(double data) :
				data(data) {
		}
	};

	Node *head { };		// Points to Top

public:
	~Stack() {
		while (!isEmpty())
			pop();
	}
	void display() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	void push(double value) {
		// By design: always new node = head
		// Great match with stack!
		Node* item = new Node(value);
		item->next = head;
		head = item;

		// Tip: This code works as long as machine has more RAM
		// In industry: You may check if return is null (can't create) or not.
	}

	double pop() {
		assert(!isEmpty());
		double element = (double) head->data;
		Node* temp = head;
		head = head->next;
		delete temp;
		return element;
	}

	int peek() {
		assert(!isEmpty());
		int element = head->data;
		return element;
	}

	int isEmpty() {
		return !head;
	}

};

int operator_val(char op) {
	if (op == '^')
		return 3;
	else if(op == '*' || op == '/')
		return 2;
	else if(op == '+' || op == '-')
		return 1;
	else
		return 0;
}

string infixToPostfix(string &infix) {
	Stack operators;
	string postfix = "";

	infix += '-'; // low priority so the last cycle always gets added.
	operators.push('#'); // 0 priority for dealing with !operator.isEmbty()
	
	for(int i = 0; i < (int) infix.size(); i++) {
		if(isdigit(infix[i]) || isalpha(infix[i]))
			postfix += infix[i];
		else if(infix[i] == '(')
				operators.push('(');
		else if(infix[i] == ')') {
			while(operators.peek() != '(')
				postfix += operators.pop();
			operators.pop();
		}
		else if(infix[i] == '^' && operators.peek() == '^') // dr added this condition to the while... 
			operators.push(infix[i]); // not much of a difference I guess? unless there's many operators that are right to left associativity.
		else {
			while(operator_val(infix[i]) <= operator_val(operators.peek()))
				postfix += operators.pop();
			operators.push(infix[i]);	
		}
	}
	return postfix;
}

double calculate(double num2, double num1, char op) {
	if(op == '-')
		return (double) num1 - num2;
	else if(op == '+')
		return (double) num1 + num2;
	else if(op == '*')
		return (double) num1 * num2;
	else if(op == '/')
		return (double) num1 / num2;
	else
		return (double) pow(num1, num2);
}

double evaluate_postfix(string postfix) { // same solution
	int len_postfix = postfix.length();
	Stack stk;
	for(int i = 0; i < len_postfix; i++) {
		if(isdigit(postfix[i]))
			stk.push(postfix[i] - 48);
		else {
			double num2 = stk.pop(), num1 = stk.pop(); // pop of rational numbers (e.g. 0.5, 1.5) doen't work.
			stk.push((double) calculate(num2, num1, postfix[i]));
		}
	}
	return stk.pop();
}

string infixToPrefix(string &infix) {
	Stack operators;
	string prefix = "";
	char c;

	// wrong answer I didn't know how to deal with paranethes.
	for(int i = (int) infix.size() - 1; i >= 0; i--) {
		if(isdigit(infix[i]) || isalpha(infix[i]))
			prefix = infix[i] + prefix; // <<
		else if(infix[i] == ')')
				operators.push('(');
		else if(infix[i] == '(') {
			while(operators.peek() != '(')
				prefix += operators.pop();
			operators.pop();
		}
		else if(!operators.isEmpty() && infix[i] == '^' && operators.peek() == '^') {
			prefix = '^' + prefix;
		}
		else {
			while(!operators.isEmpty() && operator_val(infix[i]) < operator_val(operators.peek())) {
				c = operators.pop();
				prefix = c + prefix;
			}	
			operators.push(infix[i]);
		}
	}

	while(!operators.isEmpty()) {
		c = operators.pop();
		prefix = c + prefix;
	}
	return prefix;
}

string simplify(string str) {
	// CS - Can't solve.
	string ans = "";
	int str_len = str.length() + 3;
	Stack stk;
	bool sign = 1;

	str = '(' + str; // +()
	str = '+' + str;
	str += ')';

	char c;
	for(int i = 0; i < str_len; i++) {
		if(isdigit(str[i]))
			stk.push(str[i]);
		else if(str[i] == '+' || str[i] == '-') {
			if(sign) // << stk.push(str[i]);
				stk.push(str[i]);
			else {
				if(str[i] == '-')
					stk.push('+');
				else
					stk.push('-');
			}
		}
		else if(str[i] == '(') {
			c = stk.pop();
			if(c == '-')
				sign = !sign;
			else if(c == '+' && !sign)
				sign = 1;
			stk.push('(');
			stk.push(c);
		}
		// else { // ')'
		// 	sign = 1;
		// }
	}

	while(!stk.isEmpty()) {
		c = stk.pop();
		if(c == '(')
			continue;
		ans = c + ans; // hmmm..
	}
	return ans;
}

int main() {
	// 4^3^2
	// 5+4^3^2-9
	// a+b*(c^d-e)^(f+G*h)-i
	// 1+2^3^4*5-6
	// string test = "1+2^3^4*5-6";
	// cout << infixToPostfix(test);


	// 52/
	// 12+3+
	// 123*+
	// 23*4+
	// 135*+72/-
	// string test = "432^^";
	// cout << evaluate_postfix(test);

	string test = "2+(3*(4-5*2)*(9/3+6))";
	// cout << infixToPostfix(test) << '\n';
	cout << infixToPrefix(test);
	
	// 1+2-3-4+5-6-7+8

	// 1-(2-3-(4+5))-6-(7-8)
	// 1-(2-3-(4+5)+6-7)
	// string test = "1-(2-3-(4+5)+6-7)";
	// cout << simplify(test);
	return 0;
}

