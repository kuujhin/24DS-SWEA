#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INFS 987654321987654321

using namespace std;

vector<pair<int, int>> adj[100001];
vector<int> supply(100001);

long long dijkstra(int start, int N)
{
    vector<long long> dist(N + 1, INFS);
    dist[start] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        int cur = pq.top().second;
        int curDist = -pq.top().first;
        pq.pop();

        if (dist[cur] < curDist)
            continue;

        for (int i = 0; i < adj[cur].size(); ++i)
        {
            int next = adj[cur][i].first;
            int nextDist = dist[cur] + adj[cur][i].second - supply[next];

            if (dist[next] > nextDist)
            {
                if (nextDist < 0)
                    nextDist = 0;
                dist[next] = nextDist;
                pq.push({-dist[next], next});
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

        memset(adj, 0, sizeof(adj));
        supply.clear();

        for (int i = 0; i < M; ++i)
        {
            int start, end, weight;
            cin >> start >> end >> weight;
            adj[end].push_back({start, weight});
        }

        // 보급 지점 입력
        for (int i = 0; i < K; ++i)
        {
            int island;
            cin >> island >> supply[island];
        }

        cout << "#" << t << " " << dijkstra(N, N) << endl;
    }

    return 0;
}