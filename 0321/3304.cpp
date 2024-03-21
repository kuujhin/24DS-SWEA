#include <iostream>

using namespace std;

int dp[1001][1001] = {0};

int main(int argc, char **argv)
{

    // freopen("3304.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        string str1, str2;
        cin >> str1 >> str2;

        int m = str1.size();
        int n = str2.size();

        for (int j = 1; j <= m; ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                if (str1[j - 1] == str2[k - 1])
                {
                    dp[j][k] = dp[j - 1][k - 1] + 1;
                }
                else
                {
                    dp[j][k] = max(dp[j - 1][k], dp[j][k - 1]);
                }
            }
        }

        cout << "#" << i << " " << dp[m][n] << endl;
    }

    return 0;
}