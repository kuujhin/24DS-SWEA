#include <iostream>
#include <vector>

// 부분집합 : 각 원소가 포함되는 경우(1)와 포함되지 않는 경우(0)의 조합

using namespace std;

const int MAX_N = 100;		// 최대 원소의 수
const int CANDIDATE = 2;	// 후보해의 수

int K = 0;		// 부분집합을 구성하는 원소의 합이 K를 만족하는 경우를 출력하시오.
int cnt = 0;

void process_solution(int a[], int k, int n) {
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 1) {
			sum += i;
		}
	}

	if (sum == K) {
		cnt++;
		//cout << "{ ";
		//for (int i = 1; i <= n; ++i) {
		//	if (a[i] == 1) {
		//		cout << i << " ";
		//	}
		//}
		//cout << "}\n";
	}
}

int make_candidate(int a[], int k, int n, int * c) {
	c[0] = 1;	// 포함되는 경우(1)
	c[1] = 0;	// 포함되지 않는 경우(0)
	
	return 2;
}

void backtrack(int a[], int k, int n, int cSum, int tSum) {
	int c[CANDIDATE] = { 0 };	// 후보해 집합

	// 현재까지 고려한 값을 가지고 찾은 가지치기 조건
	if (cSum > K) return;
	// 앞으로 구할 수 있는 경우를 고려한 가지치기 조건
	if (cSum + tSum < K) return;

	if (k == n) {
		process_solution(a, k, n);
	}
	else {
		k++;

		int nCands = make_candidate(a, k, n, c);	// 후보해를 생성하는 작업

		for (int i = 0; i < nCands; ++i) {
			a[k] = c[i];		// 후보해 중에 하나를 선택집합에 추가

			int num = 0;
			if (a[k] == 1) {
				num = k;
			}

			// 재귀호출의 횟수를 줄여라.
			if (cSum <= K || cSum + tSum >= K) {
				backtrack(a, k, n, cSum + num, tSum - k);
			}
		}
	}
}

int main() {
	int a[MAX_N + 1] = { 0, };	// 선택 집합

	K = 4950;
	int tSum = MAX_N * (MAX_N + 1) / 2;

	backtrack(a, 0, MAX_N, 0, tSum);		// 선택 집합, 선택한 수, 모든 선택 수

	cout << cnt << endl;
	return 0;
}