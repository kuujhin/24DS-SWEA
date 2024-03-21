#include <iostream>

using namespace std;

int network[1001][1001] = {0};
int main(int argc, char **argv)
{

    // freopen("1263.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N;

        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                int temp;
                cin >> temp;
                if (temp == 0 && i != j)
                    network[i][j] = 1000000;
                else
                    network[i][j] = temp;
            }
        }

        for (int k = 1; k <= N; ++k)
        {
            for (int i = 1; i <= N; ++i)
            {
                for (int j = 1; j <= N; ++j)
                {
                    network[i][j] = min(network[i][j], network[i][k] + network[k][j]);
                }
            }
        }

        int minDistance = 1000000;

        for (int i = 1; i <= N; ++i)
        {
            int distance = 0;
            for (int j = 1; j <= N; ++j)
            {
                if (i != j && network[i][j] != 1000000)
                {
                    distance += network[i][j];
                }
            }
            minDistance = min(minDistance, distance);
        }

        cout << "#" << t << " " << minDistance << endl;
    }

    return 0;
}