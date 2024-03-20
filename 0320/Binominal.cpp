// 이항계수(Binomial coefficients) 구하기

#include <iostream>

using namespace std;

// 재귀호출을 이용한 이항 계수의 계산

int Binomial_Recursive(int n, int k) {
	if (k == 0 || n == k)
		return 1;
	else
		return Binomial_Recursive(n - 1, k - 1) + Binomial_Recursive(n - 1, k);
}

// 메모이제이션을 이용한 이항 계수의 계산

int Binomial_Memo(int n, int r) {
	static int MEMO[10][10] = { 0, };

	if (r == 0 || n == r)
		return 1;
	if (MEMO[n][r] != 0)
		return MEMO[n][r];

	MEMO[n][r] = Binomial_Memo(n - 1, r - 1) + Binomial_Memo(n - 1, r);
	return MEMO[n][r];
}

//동적 계획법을 적용한 이항계수 계산 
int min(int n1, int n2) {
	return (n1 < n2) ? n1 : n2;
}

/*
int binomial_dp(int n, int r) {
	static int dp[10][10] = { 0, };
	for (int i = 0; i < n; i++) {
		// 0 ~ i 또는 0 ~ k 까지 중 작은 것을 택함 불필요한 것을 구하지 않기 위해서 
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


// 개선된 알고리즘, 2차원 배열 --> 1차원 배열만 사용하도록 변경
// 한번 계산된 행은 다시 사용되지 않는 점을 착안하여 1차원 배열로 변경

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
			cout << "1. 이항계수 구하기 (재귀호출)" << endl;
			cout << "2. 이항계수 구하기 (메모이제이션)" << endl;
			cout << "3. 이항계수 구하기 (동적계획법1)" << endl;
			cout << "4. 이항계수 구하기 (동적계획법2)" << endl;
			cout << "5. 종료" << endl;
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
