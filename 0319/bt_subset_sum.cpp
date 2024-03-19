#include <iostream>
#include <vector>

// �κ����� : �� ���Ұ� ���ԵǴ� ���(1)�� ���Ե��� �ʴ� ���(0)�� ����

using namespace std;

const int MAX_N = 10;		// �ִ� ������ ��
const int CANDIDATE = 2;	// �ĺ����� ��

int src[10] = { 2,6,4,9,5,1,7,3,8,10 };
int K = 10;		// �κ������� �����ϴ� ������ ���� K�� �����ϴ� ��츦 ����Ͻÿ�.

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
	c[0] = 1;	// ���ԵǴ� ���(1)
	c[1] = 0;	// ���Ե��� �ʴ� ���(0)
}

void backtrack(int a[], int k, int n) {
	vector<int> c(CANDIDATE, 0);	// �ĺ��� ����

	if (k == n) {
		process_solution(a, k, n);
	}
	else {
		k++;

		make_candidate(a, k, n, c);	// �ĺ��ظ� �����ϴ� �۾�

		for (int i = 0; i < c.size(); ++i) {
			a[k] = c[i];		// �ĺ��� �߿� �ϳ��� �������տ� �߰�
			backtrack(a, k, n);
		}
	}
}

int main() {
	int a[MAX_N + 1] = { 0, };	// ���� ����

	backtrack(a, 0, 10);		// ���� ����, ������ ��, ��� ���� ��

	return 0;
}