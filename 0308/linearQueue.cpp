#include <iostream>

using namespace std;

const int QUEUE_SZ = 10;

int queue[QUEUE_SZ];
int front = -1;
int rear = -1;

bool isfull() {
	return rear >= QUEUE_SZ - 1;
}

bool isempty() {
	return front == rear;
}

void enqueue(int value) {
	if (isfull())
		cout << "Queue is Overflow !\n";
	else
		queue[++rear] = value;
}

int dequeue() {
	if (isempty())
		cout << "Queue is Underflow !\n";
	else
		return queue[++front];
}

int main() {
	/*
	for (int i = 1; i < 13; ++i) {
		enqueue(i);
	}

	while (!isempty()) {
		cout << dequeue() << " ";
	}
	cout << endl;
	*/
	
	// pro level queue operation
	for (int i = 1; i < 11; ++i) {
		queue[++rear] = i;
	}

	while (front < rear) {
		cout << queue[++front] << " ";
	}
	cout << endl;
	
}