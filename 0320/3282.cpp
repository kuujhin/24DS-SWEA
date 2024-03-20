#include <iostream>
#include <queue>

using namespace std;

int T, N, K;
int volume[100];
int cost[100];

int knapsack_DP()
{
    int dp[N + 1][K + 1];

    for (int j = 0; j <= N; ++j)
    {
        for (int k = 0; k <= K; ++k)
        {
            if (j == 0 || k == 0)
            {
                dp[j][k] = 0;
            }
            else if (volume[j - 1] > k)
            {
                dp[j][k] = dp[j - 1][k];
            }
            else
            {
                dp[j][k] = max(cost[j - 1] + dp[j - 1][k - volume[j - 1]], dp[j - 1][k]);
            }
        }
    }
    return dp[N][K];
}

int bound(int j, int k)
{
    int b = 0;
    int v = k;
    for (int i = j; i < N; ++i)
    {
        if (volume[i] <= v)
        {
            b += cost[i];
            v -= volume[i];
        }
        else
        {
            b += (cost[i] / volume[i]) * v;
            break;
        }
    }
    return b;
}

int knapsack_BestFS()
{
    // 가성비가 좋은 것부터 정렬
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            if (cost[i] / volume[i] < cost[j] / volume[j])
            {
                swap(cost[i], cost[j]);
                swap(volume[i], volume[j]);
            }

    int node[N][N][3];

    node[0][0]
}

int main(int argc, char **argv)
{

    // freopen("3282.txt", "r", stdin);

    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N >> K;

        for (int j = 0; j < N; ++j)
        {
            cin >> volume[j] >> cost[j];
        }

        // cout << "#" << i << " " << knapsack_DP() << endl;
        cout << "#" << i << " " << knapsack_BestFS() << endl;
    }

    return 0;
}