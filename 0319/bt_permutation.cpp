#include <iostream>
#include <vector>

// 순열 : 앞에서 선택한 것을 제외한 나머지가 다음 선택 대상이 된다.

using namespace std;

const int MAX_N = 10;		// 최대 원소의 수
const int CANDIDATE = MAX_N;	// 후보해의 수


void process_solution(int a[], int k, int n) {
	cout << "{ ";
	for (int i = 1; i <= n; ++i) {
		cout << a[i] << " ";
	}
	cout << "}\n";
}

int make_candidate(int a[], int k, int n, int * c) {
	int isSelection[CANDIDATE + 1] = { 0, };
	// a[]에 선택한 값을 파악
	for (int i = 1; i < k; ++i) {
		isSelection[a[i]]++;
	}

	int cIdx = 0;
	for (int i = 1; i <= n; ++i) {
		if (isSelection[i] == 0) {		// a[]에 포함되지 않은 수이면
			c[cIdx++] = i;
		}
	}

	return cIdx;
}

void backtrack(int a[], int k, int n) {
	int c[CANDIDATE] = { 0 };	// 후보해 집합
	if (k == n) {
		process_solution(a, k, n);
	}
	else {
		k++;

		int nCands = make_candidate(a, k, n, c);	// 후보해를 생성하는 작업

		for (int i = 0; i < nCands; ++i) {
			a[k] = c[i];		// 후보해 중에 하나를 선택집합에 추가
			backtrack(a, k, n);
		}
	}
}

int main() {
	int a[MAX_N + 1] = { 0, };	// 선택 집합

	backtrack(a, 0, 3);		// 선택 집합, 선택한 수, 모든 선택 수

	return 0;
}