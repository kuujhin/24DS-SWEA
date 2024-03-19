#include <iostream>
#include <vector>

// ���� : �տ��� ������ ���� ������ �������� ���� ���� ����� �ȴ�.

using namespace std;

const int MAX_N = 10;		// �ִ� ������ ��
const int CANDIDATE = MAX_N;	// �ĺ����� ��


void process_solution(int a[], int k, int n) {
	cout << "{ ";
	for (int i = 1; i <= n; ++i) {
		cout << a[i] << " ";
	}
	cout << "}\n";
}

int make_candidate(int a[], int k, int n, int * c) {
	int isSelection[CANDIDATE + 1] = { 0, };
	// a[]�� ������ ���� �ľ�
	for (int i = 1; i < k; ++i) {
		isSelection[a[i]]++;
	}

	int cIdx = 0;
	for (int i = 1; i <= n; ++i) {
		if (isSelection[i] == 0) {		// a[]�� ���Ե��� ���� ���̸�
			c[cIdx++] = i;
		}
	}

	return cIdx;
}

void backtrack(int a[], int k, int n) {
	int c[CANDIDATE] = { 0 };	// �ĺ��� ����
	if (k == n) {
		process_solution(a, k, n);
	}
	else {
		k++;

		int nCands = make_candidate(a, k, n, c);	// �ĺ��ظ� �����ϴ� �۾�

		for (int i = 0; i < nCands; ++i) {
			a[k] = c[i];		// �ĺ��� �߿� �ϳ��� �������տ� �߰�
			backtrack(a, k, n);
		}
	}
}

int main() {
	int a[MAX_N + 1] = { 0, };	// ���� ����

	backtrack(a, 0, 3);		// ���� ����, ������ ��, ��� ���� ��

	return 0;
}