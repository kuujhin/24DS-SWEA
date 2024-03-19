#include <iostream>
#include <vector>

// �κ����� : �� ���Ұ� ���ԵǴ� ���(1)�� ���Ե��� �ʴ� ���(0)�� ����

using namespace std;

const int MAX_N = 100;		// �ִ� ������ ��
const int CANDIDATE = 2;	// �ĺ����� ��

int K = 0;		// �κ������� �����ϴ� ������ ���� K�� �����ϴ� ��츦 ����Ͻÿ�.
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
	c[0] = 1;	// ���ԵǴ� ���(1)
	c[1] = 0;	// ���Ե��� �ʴ� ���(0)
	
	return 2;
}

void backtrack(int a[], int k, int n, int cSum, int tSum) {
	int c[CANDIDATE] = { 0 };	// �ĺ��� ����

	// ������� ����� ���� ������ ã�� ����ġ�� ����
	if (cSum > K) return;
	// ������ ���� �� �ִ� ��츦 ����� ����ġ�� ����
	if (cSum + tSum < K) return;

	if (k == n) {
		process_solution(a, k, n);
	}
	else {
		k++;

		int nCands = make_candidate(a, k, n, c);	// �ĺ��ظ� �����ϴ� �۾�

		for (int i = 0; i < nCands; ++i) {
			a[k] = c[i];		// �ĺ��� �߿� �ϳ��� �������տ� �߰�

			int num = 0;
			if (a[k] == 1) {
				num = k;
			}

			// ���ȣ���� Ƚ���� �ٿ���.
			if (cSum <= K || cSum + tSum >= K) {
				backtrack(a, k, n, cSum + num, tSum - k);
			}
		}
	}
}

int main() {
	int a[MAX_N + 1] = { 0, };	// ���� ����

	K = 4950;
	int tSum = MAX_N * (MAX_N + 1) / 2;

	backtrack(a, 0, MAX_N, 0, tSum);		// ���� ����, ������ ��, ��� ���� ��

	cout << cnt << endl;
	return 0;
}