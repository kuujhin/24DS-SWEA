#include <iostream>
#include <cstdio>

using namespace std;

const int HEAP_SZ = 50;

int heap[HEAP_SZ];
int heapCount = 0;

void swap(int *n1, int *n2) {
	int tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

void printHeap() {
	int pow2[] = { 1,2,4,8,16,32,64 };
	int next_level = 1;

	for (int i = 1; i < HEAP_SZ; i++) {
		if (i == pow2[next_level]) {
			cout << endl;
			next_level++;
		}

		if (heap[i] > 0) {
			cout << heap[i] << " ";
		}
	}

	cout << endl;
}

void heap_push(int value) {
	heap[++heapCount] = value;

	int current = heapCount;
	int parent = current >> 1;
	while (parent > 0 && heap[parent] > heap[current]) {
		swap(&heap[parent], &heap[current]);

		current = parent;
		parent = current >> 1;
	}
}

int heap_pop() {
	int parent = 1;
	int retValue = heap[parent];
	heap[parent] = heap[heapCount];
	heap[heapCount--] = 0;

	int child = parent << 1;	// left child
	if (child + 1 <= heapCount && heap[child] > heap[child + 1])
		child = child + 1;

	while (child <= heapCount && heap[parent] > heap[child]) {
		swap(&heap[parent], &heap[child]);

		parent = child;
		child = parent << 1;
		if (child + 1 <= heapCount && heap[child] > heap[child + 1])
			child = child + 1;
	}

	return retValue;
}

int main() {
	heap_push(14);
	heap_push(45);
	heap_push(17);
	heap_push(24);
	heap_push(87);
	heap_push(9);
	heap_push(3);

	printHeap();

	cout << "삭제한 노드 : " << heap_pop() << endl << endl;

	printHeap();

	return 0;
}