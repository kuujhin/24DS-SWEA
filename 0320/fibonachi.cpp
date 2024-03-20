#include <iostream>

using namespace std;


int fibo_recursive(int n) {
	if (n < 2)
		return n;
	else
		return fibo_recursive(n - 1) + fibo_recursive(n - 2);
}


long long fibo_memo(int n) {
	static long long memo[100] = { 0, 1, };

	if (n >= 2 && memo[n] == 0)
		memo[n] = fibo_memo(n - 1) + fibo_memo(n - 2);
	
	return memo[n];
}

long long fibo_dp(int n) {
	long long dp[100] = { 0, 1, };

	for (int i = 2; i <= n; ++i) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}

	return dp[n];
}

// sliding window기법은 메모리 사용량을 줄여 주는 기법이다.
long long fibo_slide(int n) {
	const int WND_SZ = 3;
	long long dp[WND_SZ] = { 0, 1, };

	for (int i = 2; i <= n; ++i) {
		dp[i % WND_SZ] = dp[(i - 1) % WND_SZ] + dp[(i - 2) % WND_SZ];
	}

	return dp[n % WND_SZ];
}


int main() {
	int n = 50;

	for (int i = 1; i <= n; ++i) {
		//cout << i << " : " << fibo_recursive(i) << endl;
		//cout << i << " : " << fibo_memo(i) << endl;
		//cout << i << " : " << fibo_dp(i) << endl;
		cout << i << " : " << fibo_slide(i) << endl;
	}

	return 0;
}