#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    // freopen("5685.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        int nums[N];

        for (int j = 0; j < N; ++j)
        {
            cin >> nums[j];
        }

        long long dp[N][21] = {0};

        // 첫번째 숫자를 사용해서 만들 수 있는 숫자는 자기자신 하나 밖에 없음
        dp[0][nums[0]] = 1;

        // N-2번째 숫자까지 사용해서 만들 수 있는 숫자들의 경우의 수
        for (int j = 1; j < N - 2; ++j)
        {
            for (int k = 0; k <= 20; ++k)
            {
                if (k - nums[j] >= 0)
                {
                    dp[j][k] += dp[j - 1][k - nums[j]] % 1234567891;
                }
                if (k + nums[j] <= 20)
                {
                    dp[j][k] += dp[j - 1][k + nums[j]] % 1234567891;
                }
            }
        }

        // N-1번째 숫자를 더하거나 빼서 마지막 N번째 숫자를 만드는 경우
        if (nums[N - 1] - nums[N - 2] >= 0)
            dp[N - 2][nums[N - 1]] += dp[N - 2 - 1][nums[N - 1] - nums[N - 2]];

        if (nums[N - 1] + nums[N - 2] <= 20)
            dp[N - 2][nums[N - 1]] += dp[N - 2 - 1][nums[N - 1] + nums[N - 2]];

        cout << "#" << i << " " << dp[N - 2][nums[N - 1]] % 1234567891 << endl;
    }

    return 0;
}