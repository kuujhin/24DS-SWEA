// ���װ��(Binomial coefficients) ���ϱ�

#include <iostream>

using namespace std;

// ���ȣ���� �̿��� ���� ����� ���

int Binomial_Recursive(int n, int k) {
	if (k == 0 || n == k)
		return 1;
	else
		return Binomial_Recursive(n - 1, k - 1) + Binomial_Recursive(n - 1, k);
}

// �޸������̼��� �̿��� ���� ����� ���

int Binomial_Memo(int n, int r) {
	static int MEMO[10][10] = { 0, };

	if (r == 0 || n == r)
		return 1;
	if (MEMO[n][r] != 0)
		return MEMO[n][r];

	MEMO[n][r] = Binomial_Memo(n - 1, r - 1) + Binomial_Memo(n - 1, r);
	return MEMO[n][r];
}

//���� ��ȹ���� ������ ���װ�� ��� 
int min(int n1, int n2) {
	return (n1 < n2) ? n1 : n2;
}

/*
int binomial_dp(int n, int r) {
	static int dp[10][10] = { 0, };
	for (int i = 0; i < n; i++) {
		// 0 ~ i �Ǵ� 0 ~ k ���� �� ���� ���� ���� ���ʿ��� ���� ������ �ʱ� ���ؼ� 
		for (int j = 0; j <= min(i, r); j++) {
			if (j == 0 || j == i)
				dp[i][j] = 1;
			else
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
		}
	}
	return dp[n][r];
}
*/

int Binomial_DP(int n, int k) {
	static int DP[10][10] = { 0, };

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < i + 1; j++) {
			if (j == 0 || j == i)
				DP[i][j] = 1;
			else
				DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];
		}
	}
	return DP[n][k];
}


// ������ �˰���, 2���� �迭 --> 1���� �迭�� ����ϵ��� ����
// �ѹ� ���� ���� �ٽ� ������ �ʴ� ���� �����Ͽ� 1���� �迭�� ����

int Binomial_DP2(int n, int k) {
	int DP[10] = { 0, };

	for (int i = 0; i <= n; i++) {
		for (int j = i; j >= 0; j--) {
			if (j == 0 || j == i)
				DP[j] = 1;
			else
				DP[j] = DP[j - 1] + DP[j];
		}
	}
	return DP[k];
}

int main(void) {
	int n = 0;
	int k = 0;

	int input = 0;
	int result_value = 0;

	while (input != 5) {
		cout << "input binomial n k ";
		cin >> n >> k;
		do {
			cout << "1. ���װ�� ���ϱ� (���ȣ��)" << endl;
			cout << "2. ���װ�� ���ϱ� (�޸������̼�)" << endl;
			cout << "3. ���װ�� ���ϱ� (������ȹ��1)" << endl;
			cout << "4. ���װ�� ���ϱ� (������ȹ��2)" << endl;
			cout << "5. ����" << endl;
			cin >> input;
		} while (input < 0 || input > 5);

		if (input == 5) break;

		switch (input) {
		case 1:
			result_value = Binomial_Recursive(n, k);
			break;
		case 2:
			result_value = Binomial_Memo(n, k);
			break;
		case 3:
			result_value = Binomial_DP(n, k);
			break;
		case 4:
			result_value = Binomial_DP2(n, k);
			break;
		default:
			break;
		}
		if (input != 5)
			cout << n << "C" << k << " = " << result_value << endl;
	}

	return 0;
}
