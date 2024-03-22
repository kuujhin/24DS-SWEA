#include <iostream>
#include <cstring>

using namespace std;

int nonactive[350][350][2];
int active[350][350][2];

bool isNew[350][350];

int nonactivecells = 0;
int activecells = 0;

int di[4] = {0, 0, 1, -1};
int dj[4] = {1, -1, 0, 0};

void cellDivision(int i, int j)
{
    for (int d = 0; d < 4; d++)
    {
        // 네가지 방향에 대해
        int ni = i + di[d];
        int nj = j + dj[d];

        // 비활성 된 적이 없거나 새로 생긴 경우
        if (nonactive[ni][nj][0] == 0 || isNew[ni][nj])
        {
            // 수명이 긴 쪽으로 갱신
            if (nonactive[ni][nj][0] < nonactive[i][j][0])
                nonactive[ni][nj][0] = nonactive[i][j][0];

            // 최초 전환 시에만 비활성 세포 수 증가
            if (isNew[ni][nj] == false)
                nonactivecells++;

            // 새로 생겼음을 표시
            isNew[ni][nj] = true;
        }
    }
}

void check()
{
    memset(isNew, 0, sizeof(isNew));

    for (int i = 0; i < 350; ++i)
    {
        for (int j = 0; j < 350; ++j)
        {
            // 비활성 상태인 경우
            if ((nonactive[i][j][0] > nonactive[i][j][1]) && !isNew[i][j])
            {
                // 매 턴 생명력 소진
                nonactive[i][j][1]++;

                // 생명력을 모두 소진 시 활성 상태로 전환
                if (nonactive[i][j][0] == nonactive[i][j][1])
                {
                    active[i][j][0] = nonactive[i][j][0];
                    activecells++;
                }
                else
                {
                    nonactivecells++;
                }
            }

            // 활성 상태인 경우
            else if (active[i][j][0] > active[i][j][1])
            {
                // 매 턴 생명력 소진
                active[i][j][1]++;

                // 활성 상태 1시간 후 번식
                if (active[i][j][1] == 1)
                {
                    cellDivision(i, j);
                }
                // 생명력 모두 소진하지 않았다면 활성 세포수 개수 증가
                if (active[i][j][0] != active[i][j][1])
                {
                    activecells++;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    // freopen("test.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T, N, M, K;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N >> M >> K;

        memset(nonactive, 0, sizeof(nonactive));
        memset(active, 0, sizeof(active));

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                cin >> nonactive[150 + i][150 + j][0];
            }
        }

        for (int k = 0; k < K; ++k)
        {
            nonactivecells = 0;
            activecells = 0;
            check();
        }

        cout << "#" << t << " " << nonactivecells + activecells << endl;
    }

    return 0;
}