#include <iostream>
#include <vector>
#include <queue>

#define INFS 987654321

using namespace std;

// 거꾸로 탐색
int bfs(int start, int N, vector<vector<int>> &map)
{
    queue<int> q;

    vector<int> dist(N + 1, INFS);
    dist[N] = 0;

    q.push(N);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (int i = 1; i <= N; ++i)
        {
            if (map[i][cur] != INFS && dist[i] > dist[cur] + map[i][cur])
            {
                dist[i] = dist[cur] + map[i][cur];
                if (dist[i] < 0)
                    dist[i] = 0;
                q.push(i);
            }
        }
    }

    return dist[start];
}

int main(int argc, char **argv)
{

    // freopen("test.txt", "r", stdin);

    int T, N, M, K;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N >> M >> K;

        // 인접 행렬 입력
        vector<vector<int>> map(N + 1, vector<int>(N + 1, INFS));
        for (int i = 0; i < M; ++i)
        {
            int start, end;
            cin >> start >> end >> map[start][end];
        }

        // 보급 지점 입력
        for (int i = 0; i < K; ++i)
        {
            int island, food;
            cin >> island >> food;
            for (int j = 1; j <= N; ++j)
                if (map[island][j])
                    map[island][j] -= food;
        }

        cout << "#" << t << " " << bfs(1, N, map) << endl;
    }

    return 0;
}