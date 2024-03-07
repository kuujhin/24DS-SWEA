#include <iostream>
#include <cstdio>

// �κ����� : �� ���Ұ� ���ԵǴ� ���(1)�� ���Ե��� �ʴ� ���(0)�� ����

int src[5] = { 1,2,3,4,5 };



void printArray(int *a, int n) {
	printf("{ ");
	for (int i = 0; i < n; ++i) {
		if (a[i] == 1) {
			printf("%d ", i + 1);
		}
	}
	printf("}\n");
}


void powerset_loop() {
	int bit[3] = { 0, };

	for (int i = 0; i <= 1; ++i) {
		bit[0] = i;
		for (int j = 0; j <= 1; ++j) {
			bit[1] = j;
			for (int k = 0; k <= 1; ++k) {
				bit[2] = k;
				printArray(bit, 3);
			}
		}
	}
}

void powerset_bit(int n) {
	for (unsigned int i = 0; i < (1 << n); i++) {	// (1 << n) : 2^n
		printf("{ ");
		for (unsigned int j = 0; j < n; j++) {
			if (i & (1 << j)) {				// (i & (1 << j)) : i�� j��° bit�� 1���� �˻�
				printf("%d ", j + 1);
			}
		}
		printf("} \n");
	}
}

int main() {
	printf("�κ�����(loop)\n");
	powerset_loop();


	printf("�κ�����(bit)\n");
	powerset_bit(3);

	return 0;
}