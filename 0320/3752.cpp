#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("3752.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        int score[N];
        int max_score = 0;

        for (int j = 0; j < N; ++j)
        {
            cin >> score[j];
            max_score += score[j];
        }

        int dp[N][max_score + 1] = {0};

        // 첫번째 문제를 사용해서 만들 수 있는 점수는 자기자신 하나 밖에 없음
        dp[0][score[0]] = 1;

        // N-1번째 문제까지 사용해서 만들 수 있는 점수들의 경우의 수
        for (int j = 1; j < N; ++j)
        {
            for (int k = 0; k <= max_score; ++k)
            {
                if (k - score[j] >= 0)
                {
                    dp[j][k] += dp[j - 1][k - score[j]];
                }
                dp[j][k] += dp[j - 1][k];
            }
        }

        cout << "#" << i << " " << max_score << " " << dp[N - 1][max_score] << endl;
    }

    return 0;
}