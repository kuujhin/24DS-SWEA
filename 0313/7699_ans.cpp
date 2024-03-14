#include <iostream>
#include <cstring>

constexpr auto MAX = 20;

using namespace std;

int R, C;
int answer;
char map[MAX][MAX];
bool alphabet[26];

void DFS(int y, int x, int cnt)
{
    int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    if (cnt > answer)
        answer = cnt;

    for (int i = 0; i < 4; i++)
    {
        int ny = y + d[i][0];
        int nx = x + d[i][1];

        if (nx < 0 || ny < 0 || R <= ny || C <= nx)
            continue;

        if (alphabet[map[ny][nx] - 'A'] == false)
        {
            alphabet[map[ny][nx] - 'A'] = true;
            DFS(ny, nx, cnt + 1);
            alphabet[map[ny][nx] - 'A'] = false;
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("7699.txt", "r", stdin);

    int TC;
    cin >> TC;
    for (int tc = 1; tc <= TC; tc++)
    {
        memset(alphabet, false, sizeof(alphabet));

        cin >> R >> C;
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                cin >> map[i][j];
            }
        }

        answer = 0;
        alphabet[map[0][0] - 'A'] = true;
        DFS(0, 0, 1);

        cout << "#" << tc << " " << answer << endl;
    }

    return 0;
}