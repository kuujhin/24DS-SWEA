#include <iostream>

using namespace std;

const int STACK_SZ = 10;

int stack[STACK_SZ];
int top = -1;

bool isFull() {
	//if (top >= STACK_SZ - 1)
	//	return true;
	//else
	//	return false;

	return top >= STACK_SZ - 1;
}

bool isEmpty() {
	//if (top < 0)
	//	return true;
	//else
	//	return false;
	return top < 0;
}

void push(int value) {
	if (isFull())
		cout << "Stack Overflow !\n";
	else {
		stack[++top] = value;
	}
}

int pop() {
	if (isEmpty())
		cout << "Stack Underflow !\n";
	else {
		return stack[top--];
	}
}

int peek() {
	if (isEmpty())
		cout << "Stack Underflow !\n";
	else {
		return stack[top];
	}
}


int main() {

	for (int i = 1; i < 13; ++i) {
		push(i);
	}

	while (!isEmpty()) {
		cout << pop() << " ";
	}
	cout << endl;

	/*
	// pro level stack operation
	for (int i = 1; i < 11; ++i) {
		stack[++top] = i;
	}

	while (top >= 0) {
		cout << stack[top--] << " ";
	}
	cout << endl;
	*/
}