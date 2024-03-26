#include <iostream>
#include <vector>

#define INFS 987654321

using namespace std;

int dijkstra(int start, int N, vector<vector<int>> &map, vector<int> &supply)
{
    vector<int> dist(N + 1, INFS);
    vector<bool> visited(N + 1, false);

    for (int i = 1; i <= N; ++i)
        dist[i] = map[start][i];

    while (1)
    {
        int minIdx = -1;
        int minDist = INFS;

        for (int i = 1; i <= N; ++i)
        {
            if (!visited[i] && dist[i] < minDist)
            {
                minIdx = i;
                minDist = dist[i];
            }
        }

        if (minIdx == -1)
            break;

        visited[minIdx] = true;

        for (int i = 1; i <= N; ++i)
        {
            if (dist[i] > dist[minIdx] + map[minIdx][i] - supply[i])
            {
                dist[i] = dist[minIdx] + map[minIdx][i] - supply[i];
                if (dist[i] < 0)
                    dist[i] = 0;
            }
        }
    }

    return dist[1];
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
        for (int i = 1; i <= N; ++i)
        {
            map[i][i] = 0;
        }
        for (int i = 0; i < M; ++i)
        {
            int start, end;
            cin >> start >> end >> map[end][start];
        }

        // 보급 지점 입력
        vector<int> supply(N + 1, 0);
        for (int i = 0; i < K; ++i)
        {
            int island;
            cin >> island >> supply[island];
        }

        cout << "#" << t << " " << dijkstra(N, N, map, supply) << endl;
    }

    return 0;
}