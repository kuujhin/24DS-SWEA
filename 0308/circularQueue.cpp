#include <iostream>

using namespace std;

const int QUEUE_SZ = 10;

int queue[QUEUE_SZ];
int front = 0;
int rear = 0;

bool isfull() {
	return (rear + 1) % QUEUE_SZ == front;
}

bool isempty() {
	return front == rear;
}

void enqueue(int value) {
	if (isfull())
		cout << "Queue is Overflow !\n";
	else {
		rear = (rear + 1) % QUEUE_SZ;
		queue[rear] = value;
	}
}

int dequeue() {
	if (isempty())
		cout << "Queue is Underflow !\n";
	else
	{
		front = (front + 1) % QUEUE_SZ;
		return queue[front];
	}
}

int main() {
	
	for (int i = 1; i < 13; ++i) {
		enqueue(i);
	}

	while (!isempty()) {
		cout << dequeue() << " ";
	}

	enqueue(15);
	enqueue(30);

	cout << endl;
	
}