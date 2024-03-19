#include <iostream>
#include <vector>

// 부분집합 : 각 원소가 포함되는 경우(1)와 포함되지 않는 경우(0)의 조합

using namespace std;

const int MAX_N = 10;		// 최대 원소의 수
const int CANDIDATE = 2;	// 후보해의 수

int src[10] = { 2,6,4,9,5,1,7,3,8,10 };
int K = 10;		// 부분집합을 구성하는 원소의 합이 K를 만족하는 경우를 출력하시오.

void process_solution(int a[], int k, int n) {
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 1) {
			sum += src[i - 1];
		}
	}

	if (sum == K) {
		cout << "{ ";
		for (int i = 1; i <= n; ++i) {
			if (a[i] == 1) {
				//cout << i << " ";
				cout << src[i - 1] << " ";
			}
		}
		cout << "}\n";
	}
}

void make_candidate(int a[], int k, int n, vector<int>& c) {
	c[0] = 1;	// 포함되는 경우(1)
	c[1] = 0;	// 포함되지 않는 경우(0)
}

void backtrack(int a[], int k, int n) {
	vector<int> c(CANDIDATE, 0);	// 후보해 집합

	if (k == n) {
		process_solution(a, k, n);
	}
	else {
		k++;

		make_candidate(a, k, n, c);	// 후보해를 생성하는 작업

		for (int i = 0; i < c.size(); ++i) {
			a[k] = c[i];		// 후보해 중에 하나를 선택집합에 추가
			backtrack(a, k, n);
		}
	}
}

int main() {
	int a[MAX_N + 1] = { 0, };	// 선택 집합

	backtrack(a, 0, 10);		// 선택 집합, 선택한 수, 모든 선택 수

	return 0;
}