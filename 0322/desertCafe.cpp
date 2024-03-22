#include <iostream>
#include <cstring>

using namespace std;

int T, N;

int map[20][20];
int maxCount = -1;
int visited[101];

int di[4] = {1, 1, -1, -1};
int dj[4] = {1, -1, -1, 1};

bool check(int len, int type, int i, int j)
{
    int count = 1;
    while (count <= len)
    {
        if (visited[map[i + di[type] * count][j + dj[type] * count]] == 1)
        {
            return true;
        }
        visited[map[i + di[type] * count][j + dj[type] * count]] = 1;
        count++;
    }
    return false;
}

void tour(int i, int j)
{
    // for (int p = 1; p + j <= N - 1; ++p)
    for (int p = N - 1 - j; p >= 1; --p)
    {
        // for (int q = 1; q <= j; ++q)
        for (int q = j; q >= 1; --q)
        {
            if (2 * (p + q) <= maxCount)
                continue;
            if (p + q + i > N - 1)
                continue;

            memset(visited, 0, sizeof(visited));
            visited[map[i][j]] = 1;

            if (check(p, 0, i, j))
                continue;

            if (check(q, 1, i + p, j + p))
                continue;

            if (check(p, 2, i + p + q, j + p - q))
                continue;

            if (check(q - 1, 3, i + q, j - q))
                continue;

            maxCount = max(maxCount, 2 * (p + q));
        }
    }
}

int main(int argc, char **argv)
{

    // freopen("test.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N;

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cin >> map[i][j];
            }
        }

        maxCount = -1;

        for (int i = 0; i < N - 2; ++i)
        {
            for (int j = 1; j < N - 1; ++j)
            {
                tour(i, j);
            }
        }

        cout << "#" << t << " " << maxCount << endl;
    }

    return 0;
}