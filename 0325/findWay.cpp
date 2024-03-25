#include <iostream>
#include <vector>
#include <set>

using namespace std;

int di[4] = {0, 0, 1, -1};
int dj[4] = {1, -1, 0, 0};

void painting(int i, int j, int color, vector<vector<int>> &map)
{
    map[i][j] = color;
    for (int k = 0; k < 4; ++k)
    {
        int a = i + di[k];
        int b = j + dj[k];
        if (map[a][b] == 0)
        {
            painting(a, b, color, map);
        }
    }
}

int main(int argc, char **argv)
{

    // freopen("test.txt", "r", stdin);
    int T, N, M;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N >> M;
        vector<vector<int>> map(N + 2, vector<int>(N + 2, 1));

        int color = 2;

        // 입력
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                cin >> map[i][j];
                if (map[i][j] == 0)
                {
                    if (map[i - 1][j] != 1)
                    {
                        map[i][j] = map[i - 1][j];
                    }
                    else if (map[i][j - 1] != 1)
                    {
                        map[i][j] = map[i][j - 1];
                    }
                    else
                    {
                        map[i][j] = color++;
                    }
                }
            }
        }

        vector<int[2]> colorParent;

        // 연결된 색 체크
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (map[i][j] == 1)
                    continue;
                if (map[i - 1][j] != 1 && map[i - 1][j] != map[i][j])
                {
                }
            }
        }

        // 같은 색인지 확인하여 출력
        cout << "#" << t;
        for (int i = 0; i < M; ++i)
        {
            int A, B, C, D;
            cin >> A >> B >> C >> D;

            cout << " ";
            cout << (map[A][B] == map[C][D]);
        }
        cout << endl;
    }

    return 0;
}
