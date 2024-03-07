#include <iostream>
#include <cstdio>

// 순열의 핵심 개념 : 앞에서 선택한 것을 제외한 나머지가 다음 선택 대상이 된다.

// nPn
void perm_loop() {
	for (int i = 1; i < 4; ++i) {
		for (int j = 1; j < 4; ++j) {
			if (j == i) continue;
			for (int k = 1; k < 4; ++k) {
				if (k == j || k == i) continue;
				printf("{ %d %d %d }\n", i, j, k);
			}
		}
	}
	printf("\n");
}

void swap(int* n1, int* n2) {
	int tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

int arr[5] = { 1,2,3,4,5 };

void printArray(int *a, int n) {
	printf("{ ");
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("}\n");
}

// nPn
void perm_recursive(int k, int n) {
	if (k == n) {
		printArray(arr, n);
	}
	else
	{
		for (int i = k; i < n; ++i) {
			swap(&arr[i], &arr[k]);
			perm_recursive(k + 1, n);
			swap(&arr[i], &arr[k]);
		}
	}
}

int t[5] = { 0, };
// nPr = n * (n-1)P(r-1), (r <= n)
void perm_nPr(int n, int r, int q) {
	if (r == 0) {	// r : 뽑아야 될 갯수, 모든 선택이 완료되었으면
		printArray(t, q);	// r의 복사본, r이 감소되어 원래의 r을 알 수가 없다.
	}
	else
	{
		for (int i = n - 1; i >= 0; --i) {
			swap(&arr[i], &arr[n - 1]);
			t[r - 1] = arr[n - 1];			// n
			perm_nPr(n - 1, r - 1, q);		// (n-1)P(r-1)
			swap(&arr[i], &arr[n - 1]);
		}
	}
}


// nPIr = n * (n)PI(r-1), (r <= n), nPIr = n^r
void perm_nPIr(int n, int r, int q) {
	if (r == 0) {			// r : 뽑아야 될 갯수, 모든 선택이 완료되었으면
		printArray(t, q);	// r의 복사본, r이 감소되어 원래의 r을 알 수가 없다.
	}
	else
	{
		for (int i = n - 1; i >= 0; --i) {
			swap(&arr[i], &arr[n - 1]);
			t[r - 1] = arr[n - 1];			// n
			perm_nPIr(n, r - 1, q);		// (n)PI(r-1)
			swap(&arr[i], &arr[n - 1]);
		}
	}
}

int main() {
	printf("순열(loop)\n");
	perm_loop();


	printf("순열(재귀)\n");
	perm_recursive(0, 3);
	printf("\n");

	printf("순열(점화식)\n");
	perm_nPr(3, 3, 3);
	printf("\n");


	printf("중복순열(점화식)\n");
	perm_nPIr(3, 3, 3);
	printf("\n");


	return 0;
}